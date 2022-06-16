import express from "express";
import cors from "cors";
//import base from "./base.js";
import {MongoClient} from "mongodb"

const app = express();

const port = process.env.PORT || 9000;

app.use(cors());
app.use(express.json());


app.get('/', (req, res) => {
	res.send("Hello World!");
});


app.post('/register',(req,res)=>{
	
	console.log(req.body.username);
	console.log(req.body.password);
	registerDB({username: req.body.username , password: req.body.password});
	
});

 app.post('/login',async (req,res)=>{
	
	const loginInfo = await loginDB(req.body.username);
	if (loginInfo) {
		console.log(loginInfo.password);
	if(req.body.password === loginInfo.password){
		console.log("Password match")
		res.send("true");
	}else{
		console.log("Password dont match")
		res.send("false");
	}
	}else{
		console.log("user not registered")
		res.send("false");
	}
	
	
});

app.post('/user',(req,res)=>{
	console.log("data from client:");
	console.log(req.body);
	res.download("C:/Users/seba2/Documents/GitHub/CloudDrive_CE2103/API/test.api/src/hifumi.png");


	
});

async function registerDB(user){
    const uri = "mongodb+srv://projectApiManager:hjO95g-53f@cluster1beta.a0ttd.mongodb.net/?retryWrites=true&w=majority";

    const client = new MongoClient(uri);
    try{
        await client.connect();

        const result = await client.db("testDatabase").collection("loginsCollectionTest").insertOne(user);
    	console.log(`New listing created with the following id: ${result.insertedId}`);

        
    } catch (e) {
        console.error(e);
    } finally {
        await client.close();
    }
}

async function loginDB(user){
    const uri = "mongodb+srv://projectApiManager:hjO95g-53f@cluster1beta.a0ttd.mongodb.net/?retryWrites=true&w=majority";

    const client = new MongoClient(uri);
    try{
        await client.connect();

		const result=await client.db("testDatabase").collection("loginsCollectionTest").findOne({username:user});

		if(result){
			console.log(`Found a listing in the collection with the name '${user}'`);
			console.log(result);
			return result;
		}else{
			console.log(`No listings found with the name '${user}'`);
			return false;
		}
        
    } catch (e) {
        console.error(e);
    } finally {
        await client.close();
    }
}


app.listen(port , () => {
	console.log('Example app listening at http://localhost:'+port);
});

