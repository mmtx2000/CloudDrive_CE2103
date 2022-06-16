const apiPORT = "http://localhost:9000"

export async function fetchAPI(inputURL,username){
    console.log(inputURL);
    const response = await fetch(apiPORT+inputURL+'?keyword='+username);
    console.log(apiPORT+inputURL+'?keyword='+username);
    return response.text();
    
}
