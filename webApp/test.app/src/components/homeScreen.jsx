import React, { Component } from 'react';
import {Link} from "react-router-dom";

class HomeScreen extends Component {
    state = {  } 

    butooClicked =()=>{
      fetch("http://localhost:9000").then(res => res.blob())
      .then(blob => {
        const url = window.URL.createObjectURL(blob);
        const a = document.createElement("a");
        a.style.display = "none";
        a.href = url;
        // the filename you want
        a.download = "hifumi.png";
        document.body.appendChild(a);
        a.click();
        window.URL.revokeObjectURL(url);
        alert("your file has downloaded!"); // or you know, something with better UX...
      })
      .catch(() => alert("oh no!"));
    }

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
        <button onClick={this.butooClicked}>prapra</button>
        </div>
       
    </div>;
    }
}
 
export default HomeScreen;