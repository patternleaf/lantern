import xs from 'xstream'
import dropRepeats from 'xstream/extra/dropRepeats'
import throttle from 'xstream/extra/throttle'
import debounce from 'xstream/extra/debounce'
import dropUntil from 'xstream/extra/dropUntil'
import {div, li, h2, input, button} from '@cycle/dom';

let mouseMove$, mouseUpOut$

const between = (start, end) => source => start.mapTo(source.endWhen(end)).flatten()

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
    const drag$ = mouseMove$.compose(between(mouseDown$, mouseUpOut$))
    return xs.combine(drag$, dimensions$).map(([dragEvent, dimensions]) => {
        return {
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
    return drag$.map(drag => ({ requestedFader: drag.elementXNrm }))
}

function model(action$, initialServerFader$) {    
    const reducer$ = xs.combine(action$, initialServerFader$).map(([action, initialFader]) => (prevState) => {
        let requestedFader = action.requestedFader || prevState.requestedFader || initialFader

        if (prevState.channelIndex === 0) {
            console.log('[FADER REDUCER  ]   action', action, 'prevState', prevState, 'initialFader', initialFader)
            console.log('[FADER REDUCER  ]   *********** requested fader', requestedFader)
        }
        
        return ({
            ...prevState,
            requestedFader: requestedFader
        })
    })

    return reducer$
}

function view(state$) {
    return state$.map(state => {
        const remoteWidth = (state.fader * 100).toFixed(3)
        const knobLeft = (state.requestedFader * 100).toFixed(3)
        if (state.channelIndex === 0)
            console.log(`[view ${state.channelIndex}   ] ----> requested: ${state.requestedFader} server: ${state.fader}`)
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
        if (state.channelIndex === 0) console.log('[fader server sink]  channel 0 state', state)
        const shouldSend = !!(state.fader && state.requestedFader && (Math.abs(state.requestedFader - state.fader) > 0.001))
        if (shouldSend) {
            return {
                command: 'setFader',
                channel: state.channelIndex,
                value: state.requestedFader
            }
        }
    })

    const requestSink$ = faderSink$.mapTo({ command: 'sendState' })
    const serverSink$ = xs.merge(faderSink$, requestSink$.compose(throttle(60)))

    return {
        DOM: vdom$,
        onion: reducer$,
        server: serverSink$
    }
}