import xs from 'xstream'
// import isolate from '@cycle/isolate'
import {div, li, h2, input, button} from '@cycle/dom';

function renderSlider(serverFader, requestedFader) {
    return div('.slider', [
        div(`server: ${serverFader}, requested: ${requestedFader}`),
        input('.slider-input', {
            attrs: { type: 'range', min: 0, max: 1, step: 0.01, value: serverFader }
        })
    ]);
}

function intent(domSource) {
    return domSource.select('.slider-input').events('input').map(event => parseFloat(event.target.value))
}

function model(action$) {
    const faderReducer$ = action$.map(action => {
        // console.log('fader reducer def')
        return (prevState) => {
            // console.log('action', action, 'prevState', prevState)
            return {
                ...prevState,
                requestedFader: action
            }
        }
    })
    return faderReducer$
    return xs.merge(faderReducer$)
}

function view(state$) {
    return state$.map(state => {
        // console.log('channel', state.channelIndex, 'state', state)
        return li('.channel', [
            h2(state.effect.name),
            renderSlider(state.fader, state.requestedFader)
        ])
    })
    
}

export default function(sources) {
    const state$ = sources.onion.state$
    const action$ = intent(sources.DOM)
    const reducer$ = model(action$)
    const vdom$ = view(state$)

    const serverSink$ = xs.combine(state$, action$).map(([state, action]) => {
        console.log('server sink', state.channelIndex, state.requestedFader)
        return {
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