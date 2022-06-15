const { MongoClient }= require('mongodb');

async function main(){
    const uri = "mongodb+srv://projectApiManager:hjO95g-53f@cluster1beta.a0ttd.mongodb.net/?retryWrites=true&w=majority";

    const client = new MongoClient(uri);
    try{
        await client.connect();

        await findOneListingbyName(client, "Testing the database 1");

        
    } catch (e) {
        console.error(e);
    } finally {
        await client.close();
    }
}

main().catch(console.error);

async function findOneListingbyName(client, nameOfListing){
    const result=await client.db("testDatabase").collection("testCollection").findOne({name:nameOfListing});

    if(result){
        console.log(`Found a listing in the collection with the name '${nameOfListing}'`);
        console.log(result);
    }else{
        console.log(`No listings found with the name '${nameOfListing}'`);
    }

}


async function createMultipleListings(client, newListings){
    const result = await client.db("testDatabase").collection("testCollection").insertMany(newListings);

    console.log(`${result.insertedCount} new listings created with the following (s):`);
    console.log(result.insertedIds);
}

//creates a listing to add to the mongodb 
async function createListing(client, newListing){
    const result = await client.db("testDatabase").collection("testCollection").insertOne(newListing);
    console.log(`New listing created with the following id: ${result.insertedId}`);
}

//prints the databases available in the console
async function listDatabases(client){
    const databasesList = await client.db().admin().listDatabases();
    console.log("Databases:");
    databasesList.databases.forEach(db => {
        console.log(`-${db.name}`);
    })
}