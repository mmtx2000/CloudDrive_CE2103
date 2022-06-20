import express from "express";
import cors from "cors";
import { MongoClient} from "mongodb"
//import fs from "fs"
import fileupload from "express-fileupload"




const app = express();

const port = process.env.PORT || 9000;

app.use(cors());
app.use(express.json());
app.use(fileupload());




//recibe peticiones del cliente para subir archivos a la base de datos
app.post('/user/upload', async (req, res, next) => {
    console.log("file received");
	console.log(req.query.keyword);
    //console.log(req.files);
    if (!req.files) {
        res.send("File was not found");
        return;
      }
    
      const file = req.files.upload;
      console.log(file);
      addFileDB(req.query.keyword,file);
      //console.log();
      res.send("file uploaded!!!");
    
    
  });

//recibe peticiones del cliente para descargar archivos de la base de datos
app.post('/user/download',async (req, res) => {
	const user =req.body.username;
	const fileName = req.body.fileToDownload;
	console.log(user);
	console.log(fileName);
	const tempFile = await getFileDB(user,fileName);
	//console.log(tempFile.file);
	const userFiles = tempFile.file;
	for (let x = 0; x < userFiles.length; x++) {

		if(userFiles[x].name === fileName){
			res.send(userFiles[x]);
			break
		}

	}

});



//recibe peticiones del usuario para registarse en la base de datos
app.post('/register',(req,res)=>{
	
	console.log(req.body.username);
	console.log(req.body.password);
	registerDB({username: req.body.username , password: req.body.password, file:[]});
	res.send("true");
	
});

//recibe peticiones del cliente para iniciar sesion
 app.post('/login',async (req,res)=>{
	
	const loginInfo = await loginDB(req.body.username);
	
	
	
	
	if (loginInfo) {
		
		console.log(loginInfo.password);
	if(req.body.password === loginInfo.password){

		console.log("Password match")

		const userFiles = loginInfo.file;
		var userFilesName = [userFiles.length];
	for (let x = 0; x < userFiles.length; x++) {

		if(userFiles[x] != null){
			userFilesName[x] = userFiles[x].name;
		}

	}

		let fileSend ={
			bool: true,
			files: userFilesName
		}
		res.send(fileSend);
	}else{
		console.log("Password dont match")
		let fileSend ={
			bool: false,
			files: []
		}
		res.send(fileSend);
	}
	}else{
		console.log("user not registered")
		let fileSend ={
			bool: false,
			files: []
		}
		res.send(fileSend);
	}
	
	
});


//funcion para registrarse en la base de datos
async function registerDB(user){
    const uri = "mongodb+srv://projectApiManager:hjO95g-53f@cluster1beta.a0ttd.mongodb.net/?retryWrites=true&w=majority";

    const client = new MongoClient(uri);
    try{
        await client.connect();

        const result = await client.db("mainProjectDatabase").collection("mainCollection").insertOne(user);
    	console.log(`New listing created with the following id: ${result.insertedId}`);

        
    } catch (e) {
        console.error(e);
    } finally {
        await client.close();
    }
}

//funcion para agregar archivos al usuario
async function addFileDB(user,fileToUpload){
    const uri = "mongodb+srv://projectApiManager:hjO95g-53f@cluster1beta.a0ttd.mongodb.net/?retryWrites=true&w=majority";

    const client = new MongoClient(uri);
    try{
        await client.connect();

        //const result = await client.db("testDatabase").collection("testCollection").insertOne(fileToUpload);
		const toAdd=await client.db("mainProjectDatabase").collection("mainCollection").findOne({username:user});
		console.log(`Found a listing in the collection with the name '${toAdd.username}'`);
		const result = await client.db("mainProjectDatabase").collection("mainCollection").updateOne({username:toAdd.username},{$push:{file:fileToUpload}});
    	console.log(`updated listing with the following id: ${result.matchedCount}`);

        
    } catch (e) {
        console.error(e);
    } finally {
        await client.close();
    }
}
//funcion para obtener archivos especificos desde la base de datos
async function getFileDB(user,fileName){
    const uri = "mongodb+srv://projectApiManager:hjO95g-53f@cluster1beta.a0ttd.mongodb.net/?retryWrites=true&w=majority";

    const client = new MongoClient(uri);
    try{
        await client.connect();

		const result=await client.db("mainProjectDatabase").collection("mainCollection").findOne({username:user});
		//console.log(`Found a listing in the collection with the name '${toAdd.username}'`);
		//const result=await client.db("testDatabase").collection("testCollection").findOne({username:user});
		console.log(`Found a listing in the collection with the name '${result.username}'`);
		if(result){
			console.log(`Found a listing in the collection with the name '${fileName}'`);
			//console.log(result);
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

//funcion para llamar a la base de datos y obtener un usuario especifico
async function loginDB(user){
    const uri = "mongodb+srv://projectApiManager:hjO95g-53f@cluster1beta.a0ttd.mongodb.net/?retryWrites=true&w=majority";

    const client = new MongoClient(uri);
    try{
        await client.connect();
		
		const result=await client.db("mainProjectDatabase").collection("mainCollection").findOne({username:user});

		if(result){
			console.log(`Found a listing in the collection with the name '${user}'`);
			//console.log(result);
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

