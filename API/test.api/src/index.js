import express from "express";
import cors from "cors";
import {MongoClient} from "mongodb"
import formidable from "formidable"
import fileupload from "express-fileupload"

const app = express();

const port = process.env.PORT || 9000;

app.use(cors());
app.use(express.json());
app.use(fileupload());


app.get('/', (req, res) => {
	//res.send("Hello World!");
	res.download("C:/Users/seba2/Documents/GitHub/CloudDrive_CE2103/API/test.api/hifumi.png");
});

app.get('/user/download', (req, res) => {
	//res.send("Hello World!");
	const tempFile = getFileDB("hifumi (1).png ");
	console.log(tempFile);
	res.download(tempFile);
});


app.post('/user/upload', async (req, res, next) => {
	console.log("file received");
	//console.log(req.files);
	if (!req.files) {
		res.send("File was not found");
		return;
	  }
	
	  const file = req.files.upload;
	  console.log(file.name);
	  addFileDB(file);
	  //console.log();
	  res.send(file);
	
	
  });

app.post('/register',(req,res)=>{
	
	console.log(req.body.username);
	console.log(req.body.password);
	registerDB({username: req.body.username , password: req.body.password});
	res.send("true");
	
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

app.post('/user/download',(req,res)=>{
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

async function addFileDB(fileToUpload){
    const uri = "mongodb+srv://projectApiManager:hjO95g-53f@cluster1beta.a0ttd.mongodb.net/?retryWrites=true&w=majority";

    const client = new MongoClient(uri);
    try{
        await client.connect();

        const result = await client.db("testDatabase").collection("testCollection").insertOne(fileToUpload);
    	console.log(`New listing created with the following id: ${result.insertedId}`);

        
    } catch (e) {
        console.error(e);
    } finally {
        await client.close();
    }
}

async function getFileDB(fileName){
    const uri = "mongodb+srv://projectApiManager:hjO95g-53f@cluster1beta.a0ttd.mongodb.net/?retryWrites=true&w=majority";

    const client = new MongoClient(uri);
    try{
        await client.connect();

		const result=await client.db("testDatabase").collection("testCollection").findOne({name:fileName});

		if(result){
			console.log(`Found a listing in the collection with the name '${fileName}'`);
			console.log(result);
			return result;
		}else{
			console.log(`No listings found with the name '${fileName}'`);
			return false;
		}
        
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

