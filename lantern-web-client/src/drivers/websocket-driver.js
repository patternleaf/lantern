import xs from 'xstream'
import {adapt} from '@cycle/run/lib/adapt';

export default function(url) {
    let connection = new WebSocket(url);

    function driver(outgoing$) {
        outgoing$.addListener({
            next: outgoing => {
                if (typeof outgoing === 'string') {
                    connection.send(outgoing);
                }
                else if (outgoing) {
                    console.log('outgoing', outgoing)
                    connection.send(JSON.stringify(outgoing));
                }
            },
            error: () => {},
            complete: () => {},
        });

        const incoming$ = xs.create({
            start: listener => {
                connection.onmessage = msg => {
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