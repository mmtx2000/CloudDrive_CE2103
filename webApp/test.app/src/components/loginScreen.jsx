import React, {Component} from 'react';
import {fetchAPI} from './CallAPIService.js';
import {Link} from "react-router-dom";


class LoginScreen extends Component {
    state = {  

    APImessage: '',
    userName: '',
    userPassword: ''
 } 


    buttonClicked =() =>{
        console.log("click");
        //this.setState({userinput:});
        fetchAPI(window.location.pathname,this.state.userName+this.state.userPassword).then(response => this.setState({APImessage: response}));
        console.log(this.state.userName);
        console.log(this.state.userPassword);
        
    }

    handleChange =(event) => {
        
        //this.setState({value: event.target.value});
        this.setState({[event.target.name]: event.target.value});
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
        </div>
        
        <div style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '10vh',
        
      }}>
        
        <span>{this.state.APImessage}</span>
        </div>

        <div style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '10vh',
        
      }}>
        <label>Username
        <input type="text" name='userName' value={this.state.value} onChange={this.handleChange}/>
        </label>
        <label>Password
        <input type="password" name='userPassword' value={this.state.value} onChange={this.handleChange}/>
        </label>
        
        </div>
        <div style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '10vh',
        
      }}>
        <button 
        onClick={this.buttonClicked}
        className = "btn btn-primary btn-sm">Log In</button>
        </div>
        <div style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '10vh',
        
      }}>
        
        <Link to = "/"><button className = "btn btn-secondary btn-sm">Home</button></Link>
        </div>
       
    </div>; ;
    }
}
 
export default LoginScreen;