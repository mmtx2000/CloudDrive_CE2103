import express from "express";
import cors from "cors";
import base from "./base.js";
//const express =require("express");
//const cors = require("cors");

const app = express();

const port = process.env.PORT || 9000;

app.use(cors());
app.use(express.json());



app.get('/', (req, res) => {
	res.send("Hello World!");
});


app.post('/login',(req,res)=>{
	
	console.log(req.body.username);
	console.log(req.body.password);
	//base.testBase();
});
app.post('/user',(req,res)=>{
	res.download("./hifumi.png");
	//console.log(req.body.username);
	//console.log(req.body.password);
	//base.testBase();
});
app.listen(port , () => {
	console.log('Example app listening at http://localhost:'+port);
});

