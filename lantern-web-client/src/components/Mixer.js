import xs from 'xstream'
// import isolate from '@cycle/isolate'
import {div, ul, button} from '@cycle/dom';
import Channel from './Channel'
import { makeCollection } from 'cycle-onionify';
import isolate from '@cycle/isolate';


function intent(domSource) {
    return {
        requests$: domSource.select('.request-state').events('click').map(() => ({ command: 'sendState' }))
    }
}

function model(actions, sources) {
    const initMixerReducer$ = xs.of(() => { return { channels: [] } })
    const mixerReducer$ = sources.server.map(state => { return (prevState) => {
        return {
            ...state,
            channels: state.channels.map((channel, i) => ({
                ...channel,
                channelIndex: i
            }))
        }
    }})
    const reducer$ = xs.merge(initMixerReducer$, mixerReducer$)
    return reducer$
}

function view(state$, channelDOM$) {
    return xs.combine(state$, channelDOM$).map(([mixerState, channelVNodes]) => {
        return div('.server-state', [
            button('.request-state', 'Request State'),
            channelVNodes
        ])
    })
    // return state$.map(state => {
    //     // console.log('hi there', state)
    //     return div('.server-state', [
    //         button('.request-state', 'Request State'),
    //         // ul('.channels', state.channels.map((channel, i) => {
    //         //     return (div(`#effect-${channel.effect.id}.effect-key-${channel.effectKey}`, channel.effect.name))
    //         // }))
    //         channelSinks.DOM
    //     ])
    // })
}

function ChannelList(sources) {
    const ChannelCollection = makeCollection({
        item: Channel,
        itemKey: (childState, index) => index,//childState.effect.id,
        itemScope: key => key,
        collectSinks: instances => {
            return {
                onion: instances.pickMerge('onion'),
                DOM: instances.pickCombine('DOM').map(itemVNodes => (ul(itemVNodes))),
                server: instances.pickMerge('server')
            }
        }
    })
    const channelSinks = ChannelCollection(sources)

    return channelSinks
}

export default function(sources) {
    const channelSinks = isolate(ChannelList, 'channels')(sources)
    const actions = intent(sources.DOM)
    const mixerReducer$ = model(actions, sources)

    return {
        onion: xs.merge(mixerReducer$, channelSinks.onion),
        DOM: view(sources.onion.state$, channelSinks.DOM),
        server: xs.merge(actions.requests$, channelSinks.server)
    }
}