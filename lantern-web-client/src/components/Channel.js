import xs from 'xstream'
import isolate from '@cycle/isolate'
import {div, li, h2, input, button} from '@cycle/dom';
import AsyncFader from './AsyncFader'


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
    const faderLens = {
        get: state => state,
        set: (state, childState) => ({ ...state, ...childState })
    }
    const faderSinks = isolate(AsyncFader, { onion: faderLens })(sources)
    const vdom$ = view(state$, faderSinks)

    return {
        DOM: vdom$,
        onion: faderSinks.onion,
        server: faderSinks.server
    }
}