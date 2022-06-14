import express from "express";
import cors from "cors";
import mongoose from "mongoose";

const app = express();
const port = process.env.PORT || 9000;

app.use(cors());




app.get('/', (req, res) => {
	res.send("Hello World!");
});

app.get('/login',(req,res)=>{
	
	printName(req.query.keyword);
	res.send("prapra login momento para mi pana: "+req.query.keyword);
});

app.listen(port , () => {
	console.log('Example app listening at http://localhost:'+port);
});

async function printName(username){
	console.log(username);
}