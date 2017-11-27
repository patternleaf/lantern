import xs from 'xstream'
import dropRepeats from 'xstream/extra/dropRepeats'
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

function model(action$) {
    // const initialReducer$ = xs.of(() => ({ effect: { name: '' }, fader: 0, requestedFader: 0 }))
    const dragReducer$ = action$.map(action => (prevState) => {
        return ({
            ...prevState,
            requestedFader: action.requestedFader
        })
    })
    return xs.merge(/*initialReducer$,*/ dragReducer$)
}

function view(state$) {
    return state$.map(state => {
        const remoteWidth = (state.fader * 100).toFixed(3)
        const knobLeft = (state.requestedFader * 100).toFixed(3)
        return (
            <div className="async-fader">
                <div className="remote-level" style={`width: ${remoteWidth}%`}></div>
                <div className="knob" style={`left: ${knobLeft}%`}></div>
            </div>
        )
    })
}

export default function(sources) {
    const state$ = sources.onion.state$
    const action$ = intent(sources.DOM)
    const reducer$ = model(action$)
    const vdom$ = view(state$)

    const serverSink$ = state$.map(state => {
        return state.requestedFader && {
            command: 'setFader',
            channel: state.channelIndex,
            value: state.requestedFader
        }
    })

    return {
        DOM: vdom$,
        onion: reducer$,
        server: serverSink$
    }
}