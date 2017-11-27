import {run} from '@cycle/run'
import {makeDOMDriver} from '@cycle/dom'
import App from './app'
import makeWebsocketDriver from './drivers/websocket-driver'
import './styles/main.less'

const main = App

const drivers = {
  DOM: makeDOMDriver('#root'),
  server: makeWebsocketDriver('ws://localhost:9002')
}

run(main, drivers)
