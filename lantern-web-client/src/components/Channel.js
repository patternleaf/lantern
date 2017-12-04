import xs from 'xstream'
import isolate from '@cycle/isolate'
import {div, li, h2, input, button} from '@cycle/dom';
import AsyncFader from './AsyncFader'

// function renderSlider(serverFader, requestedFader) {
//     return (
//         <div className="slider">
//             <div>server: {serverFader}, requested: {requestedFader}</div>
//             <input className="slider-input" type="range" min="0" max="1" step="0.01" value={serverFader}/>
            
//         </div>
//     )
// }

function intent(domSource) {
    return domSource.select('.slider-input').events('input').map(event => parseFloat(event.target.value))
}

function model(action$) {
    /*
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
    */
}

function view(state$, faderSinks) {
    return xs.combine(state$, faderSinks.DOM).map(([state, faderVDOM]) => {
        return (
            <li className="channel">
                <h2>{state.effect.name}</h2>
                {faderVDOM}
            </li>
        )
    })   
}

export default function(sources) {
    const state$ = sources.onion.state$
    const action$ = intent(sources.DOM)
    // const reducer$ = model(action$)
    const faderLens = {
        get: state => state,
        set: (state, childState) => { 
            if (childState.channelIndex === 0) 
                console.log('[FADER LENS SET] state', { ...state, ...childState }); 
            return ({ ...state, ...childState })
        }
    }
    const faderSinks = isolate(AsyncFader, { onion: faderLens })(sources)
    const vdom$ = view(state$, faderSinks)

    return {
        DOM: vdom$,
        onion: faderSinks.onion,
        server: faderSinks.server
    }
}