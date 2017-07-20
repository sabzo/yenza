// wrap internal _recommend funnction to a js function
var recommend = Module.cwrap('_recommend', null, ['string']);
// form 
var submit = document.getElementById("submit");
var uid = document.getElementById("uid");
submit.onclick = function() {
 recommend(uid.value.toString());
}

