import React, {Component} from 'react';
import {fetchAPI} from './CallAPIService.js';
import {Link} from "react-router-dom";


class RegisterScreen extends Component {
    state = {  

    APImessage: '',
    userName: '',
    userPassword: ''
 } 


    buttonClicked =() =>{
        console.log("click");
        
        const requestOptions = {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ username: this.state.userName,
          password: this.state.userPassword })
      };
        fetch('http://localhost:9000'+window.location.pathname, requestOptions);
        
        
    }
    buttonRegister=()=>{
      console.log("click");
        
        const requestOptions = {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ username: this.state.userName,
          password: this.state.userPassword })
      };
        fetch('http://localhost:9000'+window.location.pathname, requestOptions);
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
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        height: '10vh'
        
        
      }}>
        <label>Username
        <input type="text" name='userName' value={this.state.value} onChange={this.handleChange}/>
        </label>
        
        
        </div>
        <div style={{
        display: "flex",
        justifyContent: "center",
        alignItems: "center",
        
        
      }}>
        
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
        className = "btn btn-primary btn-sm">Register</button>
        </div>

        <div style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '10vh',
        
      }}>
        
        <Link to = "/"><button className = "btn btn-secondary btn-sm">Home</button></Link>
        <Link to="/login">
        <button className ="btn btn-primary btn-sm">Log in</button>
        </Link>
        </div>
       
    </div>; ;
    }
}
 
export default RegisterScreen;