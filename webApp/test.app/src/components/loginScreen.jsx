import React, {Component} from 'react';
import {Link} from "react-router-dom";
import Select from 'react-select'


class LoginScreen extends Component {
    state = {  
    isLogged: false,
    APImessage: '',
    userName: '',
    userPassword: '',
    selectedFile: null,
    uploadURL: '',
    filesToDownload: [],
    nameToDownload: ''

 } 

    //maneja el inicio de sesion del usuario
    buttonClicked =() =>{
        console.log("click");
        
        const requestOptions = {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ username: this.state.userName,
          password: this.state.userPassword })
      };
        fetch('http://localhost:9000'+window.location.pathname, requestOptions).then(res=>res.json()).then((res) => {
          console.log('Success:', res.bool);
          if(res.bool === true){
            this.setState({APImessage: "logged in!"});
            this.setState({isLogged: true});
            const filesFromDB =res.files;
            console.log(filesFromDB);
            
            for (let x = 0; x < filesFromDB.length; x++) {
              var temp = {value:filesFromDB[x],label:filesFromDB[x]};
              this.state.filesToDownload.push(temp)
            }
            console.log(this.state.filesToDownload);
          }
            else{ 
              this.setState({APImessage: "Wrong username or password"});}
          
        })
        .catch((error) => {
          console.error('Error:', error);
         
        });
        
        
    }
    //actualiza valores del archivo para enviar a la base de datos
    onFileChange = event => {
    
      // Update the state
      console.log("setting file");
      this.setState({ selectedFile: event.target.files[0] });
      this.setState({uploadURL: 'http://localhost:9000/user/upload?keyword='+this.state.userName})
    
    };
    //metodo par descargar un archivo de la base de datos
    butooClicked =()=>{
    
      const requestOptions = {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ username: this.state.userName,
          fileToDownload: this.state.nameToDownload.value })
        }
      fetch("http://localhost:9000/user/download",requestOptions).then(res => res.blob())
      .then(blob => {
        const url = window.URL.createObjectURL(blob);
        const a = document.createElement("a");
        a.style.display = "none";
        a.href = url;
        // the filename you want
        a.download = "download";
        document.body.appendChild(a);
        a.click();
        window.URL.revokeObjectURL(url);
        alert("your file has downloaded!"); // or you know, something with better UX...
      })
      .catch(() => alert("oh no!"));
    }

    changedValue = (nameToDownload) =>{
      //this.setState({this.state.value: event.target.value});
      this.setState({nameToDownload});
    }

      fileData = () => {
    
        if (this.state.selectedFile) {
           
          return (
            <div>
              <h2>File Details:</h2>
               
  <p>File Name: {this.state.selectedFile.name}</p>
   
               
  <p>File Type: {this.state.selectedFile.type}</p>

  <p>File content: {this.state.selectedFile.fileData}</p>
   
               
  <p>
                Last Modified:{" "}
                {this.state.selectedFile.lastModifiedDate.toDateString()}
              </p>
   
            </div>
          );
        } else {
          return (
            <div>
              <br />
              <h4>Choose before Pressing the Upload button</h4>
            </div>
          );
        }
      };
      

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
        className = "btn btn-primary btn-sm">Log In</button>
        
        
        
        </div>

        <div style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '10vh',
        
      }}>
        
        <Link to = "/"><button className = "btn btn-secondary btn-sm">Home</button></Link>
        <Link to="/register">
        <button className ="btn btn-primary btn-sm">Register</button>
        </Link>
        
        </div>
        {this.state.isLogged ?<div> <div style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '10vh'}}>
        
        <form className='form' action={this.state.uploadURL} method='POST' encType='multipart/form-data' >
        file:<input type="file" name='upload' onChange={this.onFileChange} />
        <input type='submit' className='btn btn-primary btn-sm' value={"Upload!"}/>
        </form>
        </div >
        <div style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '10vh'}}>
          {this.fileData()}
        </div>
        <div style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '10vh'}}>
          <Select options={this.state.filesToDownload}  value={this.state.nameToDownload} onChange={this.changedValue}/>
          <button className='btn btn-primary btn-sm' onClick ={this.butooClicked}>Download!</button>
        </div>
       </div> : null}
        
    </div>; ;
    }
}
 
export default LoginScreen;