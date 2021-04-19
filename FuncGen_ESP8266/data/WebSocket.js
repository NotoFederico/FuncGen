var WebSocket = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);
WebSocket.onopen = function () 
{
    WebSocket.send("Este mensaje es traido por... MAROLIO... Le da sabor a tu vida!");
};
WebSocket.onerror = function (error) {
    console.log('WebSocket Error ', error);
};
WebSocket.onmessage = function (e) { 
	document.getElementById("nuevo_mensaje").innerHTML = e.data;
	//alert("Te llegó este mensaje: " + e.data);
};
WebSocket.onclose = function(){
    console.log('WebSocket connection closed');
};
