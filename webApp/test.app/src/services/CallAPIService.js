const apiPORT = "http://localhost:9000"

export async function fetchAPI(inputURL){
    console.log(inputURL);
    const response = await fetch(apiPORT+inputURL);
    return await response.text();
}