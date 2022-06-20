import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
import { BrowserRouter, Route, Routes } from 'react-router-dom';
import reportWebVitals from './reportWebVitals';
import 'bootstrap/dist/css/bootstrap.css';
import HomeScreen from './components/homeScreen';
import LoginScreen from './components/loginScreen';
import RegisterScreen from './components/registerScreen';
import UserScreen from './components/userScreen';


const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  <BrowserRouter>
  <React.StrictMode>
  <Routes>
      <Route path="/" element={<HomeScreen />} />
      <Route path="login" element={<LoginScreen />} />
      <Route path="register" element={<RegisterScreen/>} />
      <Route path='user' element={<UserScreen/>}/>
      
    </Routes>
  </React.StrictMode>
  </BrowserRouter>
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals(console.log);
