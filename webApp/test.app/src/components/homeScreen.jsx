import React, { Component } from 'react';
import {Link} from "react-router-dom";

class HomeScreen extends Component {
    state = {  } 
    render() { 
        return <div className='div'  >
        <div style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '10vh',
        
      }}>
        <h1>CloudDrive</h1>
        <span>{this.state.APImessage}</span>
        </div>
        
        <div style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '10vh',
        
      }}>
        <Link to= "login"><button className = "btn btn-secondary btn-sm">login</button></Link>
        </div>
       
    </div>;
    }
}
 
export default HomeScreen;