import xs from 'xstream'
import Mixer from './components/Mixer'
// import isolate from '@cycle/isolate'
import onionify from 'cycle-onionify';


function App (sources) {
  const mixer = Mixer(sources)
  
  const sinks = {
		onion: mixer.onion,
		DOM: mixer.DOM,
		server: mixer.server
  }
  return sinks
}

export default onionify(App)