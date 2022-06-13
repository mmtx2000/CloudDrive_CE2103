import React, { Component } from 'react';
import {fetchAPI} from '/home/seballoll/Desktop/bot/test.app/src/services/CallAPIService.js';
import {Link} from "react-router-dom";

class Counter extends Component { 
    state = {
        message: '',
        imageURL: 'https://picsum.photos/300'
    };
    render() { 
        return <div>
            <span>{this.state.message}</span>
            <button 
            onClick={this.buttonClicked}
            className = "btn btn-secondary btn-sm">pipo</button>
            <img src={this.state.imageURL} alt=""/>
            <Link to= "login">login</Link>
            <Link to = "/">home</Link>
        </div>;
    }
    buttonClicked =() =>{
        console.log("click");
        const response = fetchAPI(window.location.pathname);
        console.log(response);
        this.setState({ message: "response"});
    }
}
 
export default Counter;