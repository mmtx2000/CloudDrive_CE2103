import React, { Component } from 'react';
import { Link } from 'react-router-dom';
import axios  from 'axios';


class UserScreen extends Component {
    state = { selectedFile: null } 

    butooClicked =()=>{
      fetch("http://localhost:9000/user/download").then(res => res.blob())
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


    onFileChange = event => {
    
        // Update the state
        this.setState({ selectedFile: event.target.files[0] });
        //this.onFileUpload();
      
      };

    onFileUpload = () => {
      const formData = new FormData();
    
      // Update the formData object
      formData.append(
        "myFile",
        this.state.selectedFile,
        this.state.selectedFile.name
      );
    
      // Details of the uploaded file
      console.log(this.state.selectedFile);
      console.log(Array.from(formData)[1]);
    
      // Request made to the backend api
      // Send formData object
      axios.post("http://localhost:9000/user/upload", formData);
    
        // Details of the uploaded file
        //console.log(this.state.selectedFile);
        
        
        
      };

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
      
    

    render() { 
        return <div className="App">
        <form className='form' action='http://localhost:9000/user/upload' method='POST' encType='multipart/form-data'>
          
  
          <input type="file" name='upload' onChange={this.onFileChange} />
          <input type='submit' value={"Upload"}/>
          <button className='btn btn-primary btn-sm' onClick ={this.butooClicked}>Download!</button>
        </form>

        <div style={{
        display: 'flex',
        justifyContent: 'center',
        alignItems: 'center',
        height: '10vh',
        
      }}>
        
        <Link to = "/"><button className = "btn btn-secondary btn-sm">Home</button></Link>
        
        </div>
        {this.fileData()}
       
      </div>;
    }
}
 
export default UserScreen;