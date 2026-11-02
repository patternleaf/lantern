import xs from 'xstream'
import {adapt} from '@cycle/run/lib/adapt';
import buffer from 'xstream/extra/buffer'
import dropUntil from 'xstream/extra/dropUntil'

export default function(url) {
    let connection = new WebSocket(url);

    const isOpen$ = xs.createWithMemory({
        start: listener => {
            connection.onopen = e => {
                listener.next()
            }
        },
        stop: () => {
        }
    })

    function driver(outgoing$) {
        
        const bufferedUntilOpen$ = outgoing$.compose(buffer(isOpen$)).take(1).map(bufferedEvents => { 
            return xs.fromArray(bufferedEvents);
        }).flatten()
        const outgoingAfterOpen$ = outgoing$.compose(dropUntil(isOpen$))

        xs.merge(bufferedUntilOpen$, outgoingAfterOpen$).addListener({
            next: outgoing => {
                if (typeof outgoing === 'string') {
                    connection.send(outgoing);
                }
                else if (outgoing) {
                    // console.log('outgoing', outgoing)
                    connection.send(JSON.stringify(outgoing));
                }
            },
            error: () => {},
            complete: () => {},
        });

        const incoming$ = xs.createWithMemory({
            start: listener => {
                connection.onmessage = msg => {
                    // console.log('incoming', JSON.parse(msg.data))
                    // const blah = JSON.parse(msg.data)
                    // listener.next({ channels: [blah.channels[0]] })
                    listener.next(JSON.parse(msg.data));
                };
                connection.onerror = error => {
                    console.log('ws error', error)
                    listener.error(error)
                }
            },
            stop: () => {
                connection.close();
            },
        });

        return adapt(incoming$);
    }

    return driver;
}