import React, { Component } from 'react';
import { Link } from 'react-router-dom';

class UserScreen extends Component {
    state = { selectedFile: null } 

    onFileChange = event => {
    
        // Update the state
        this.setState({ selectedFile: event.target.files[0] });
        this.onFileUpload();
      
      };

    onFileUpload = () => {
        const formData = new FormData();

		formData.append('File', this.selectedFile);

		fetch(
			'http://localhost:9000/user',
			{
				method: 'POST',
				body: formData,
			}
		)
			.then((response) => response.formData())
			.then((result) => {
				console.log('Success:', result);
			})
			.catch((error) => {
				console.error('Error:', error);
			});
	
        // Create an object of formData
        console.log("uploaded");
        //const formData = new FormData();
      
        // Update the formData object
        //formData.append(
          //"myFile",
          //this.state.selectedFile,
          //this.state.selectedFile.name
        //);
      
        // Details of the uploaded file
        console.log(this.state.selectedFile);
        //console.log(formData.values);
        
        //fetch("http://localhost:9000"+window.location.pathname,formData).then(res=>res.blob());
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
        <form>
          <input type="text" />
  
          <input type="file" onChange={this.onFileChange} />
          
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