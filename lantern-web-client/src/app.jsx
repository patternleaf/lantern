import xs from 'xstream'
import Mixer from './components/Mixer'
// import isolate from '@cycle/isolate'
import onionify from 'cycle-onionify';


function App (sources) {
  const mixer = Mixer(sources)
  // const pingServer = 
	// const blah = xs.of(div(['hi there']))
	
  // const vtree$ = xs.combine(lastMessage.DOM, blah)
  //   .map(([message, boilerplate]) => {
  //     div([boilerplate, message])
  //   })
  
  // const vtree$ = xs.of(div(['hi there']))
  
  const sinks = {
		onion: mixer.onion,
		DOM: mixer.DOM,
		server: mixer.server
  }
  return sinks
}

export default onionify(App)