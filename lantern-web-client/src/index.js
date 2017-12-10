import {run} from '@cycle/run'
import {makeDOMDriver} from '@cycle/dom'
import App from './app'
import makeWebsocketDriver from './drivers/websocket-driver'
import './styles/main.less'

const main = App

// const serverUrl = 'ws://localhost:9002'
const serverUrl = 'ws://10.0.0.191:9002'

const drivers = {
  DOM: makeDOMDriver('#root'),
  server: makeWebsocketDriver(serverUrl)
}

run(main, drivers)
