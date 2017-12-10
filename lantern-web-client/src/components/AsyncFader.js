import xs from 'xstream'
import dropRepeats from 'xstream/extra/dropRepeats'
import throttle from 'xstream/extra/throttle'
import debounce from 'xstream/extra/debounce'
import dropUntil from 'xstream/extra/dropUntil'
import {div, li, h2, input, button} from '@cycle/dom';

let mouseMove$, mouseUpOut$

const between = (start, end) => source => start.mapTo(source.endWhen(end)).flatten()
const betweenInclusive = (start, end) => (source) => {
    return start.map(downEvt => xs.merge(xs.of(downEvt), source.endWhen(end), end.take(1))).flatten()
}

function bindEventStreams(domSource, selector) {
    const element$ = domSource.select(selector).elements().map(([element]) => element).compose(dropRepeats())
    const mouseDown$ = domSource.select(selector).events('mousedown')
    if (!mouseMove$) {
        mouseMove$ = domSource.select('body').events('mousemove')
        mouseUpOut$ = domSource.select('body').events('mouseup')
    }
    const dimensions$ = element$.map((element) => {
        return element && { 
            width: element.offsetWidth, 
            height: element.offsetHeight, 
            top: element.offsetTop,
            left: element.offsetLeft
         }
    })
    const drag$ = mouseMove$.compose(betweenInclusive(mouseDown$, mouseUpOut$))
    return xs.combine(drag$, dimensions$).map(([dragEvent, dimensions]) => {
        return {
            eventType: dragEvent.type,
            x: dragEvent.clientX,
            y: dragEvent.clientY,
            elementXNrm: Math.min(1.0, Math.max(0.0, (dragEvent.clientX - dimensions.left) / (dimensions.width))),
            elementYNrm: Math.min(1.0, Math.max(0.0, (dragEvent.clientY - dimensions.top) / (dimensions.height))),
            dimensions,
        }
    })
}

function intent(domSource) {
    const drag$ = bindEventStreams(domSource, '.async-fader')
    return drag$.map(drag => {
        return { 
            requestedFader: drag.elementXNrm,
            isWriting: drag.eventType === 'mousemove'
        }
    })
}

function model(action$, initialServerFader$) {
    const reducer$ = xs.combine(action$, initialServerFader$).map(([action, initialServerFader]) => (prevState) => {
        let requestedFader = prevState.fader || initialServerFader
        if (action.isWriting && action.requestedFader) {
            requestedFader = action.requestedFader
        }

        return ({
            ...prevState,
            requestedFader: requestedFader,
            isWriting: action.isWriting
        })
    })

    return reducer$
}

function view(state$) {
    return state$.map(state => {
        const remoteWidth = (state.fader * 100).toFixed(3)
        const knobLeft = (state.requestedFader * 100).toFixed(3)
        return (
            <div className="async-fader">
                <div className="track"></div>
                <div className="remote-level" style={`width: ${remoteWidth}%`}></div>
                <div className="knob" style={`left: ${knobLeft}%`}></div>
            </div>
        )
    })
}

export default function(sources) {
    const state$ = sources.onion.state$
    const action$ = intent(sources.DOM).startWith({})

    const server$ = sources.server
    const initialServerFader$ = state$.map(state => state.fader).compose(dropUntil(server$)).take(1)

    const reducer$ = model(action$, initialServerFader$)
    const vdom$ = view(state$)

    const faderSink$ = state$.map(state => {
        const shouldSend = !!(state.isWriting && (state.fader !== undefined) && (state.requestedFader !== undefined) && (Math.abs(state.requestedFader - state.fader) > 0.001))
        if (shouldSend) {
            return {
                command: 'setFader',
                channel: state.channelIndex,
                value: state.requestedFader
            }
        }
    })

    return {
        DOM: vdom$,
        onion: reducer$,
        server: faderSink$
    }
}