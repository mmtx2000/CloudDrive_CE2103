import React, { Component } from 'react';

class UserScreen extends Component {
    state = { selectedFile: null } 

    onFileChange = event => {
    
        // Update the state
        this.setState({ selectedFile: event.target.files[0] });
      
      };

    render() { 
        return <div className="App">
        <form>
          <input type="text" />
  
          <input type="file" />
        </form>
      </div>
        ;
    }
}
 
export default UserScreen;