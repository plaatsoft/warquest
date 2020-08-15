/*
**  ========
**  WarQuest
**  ========
**
**  Created by wplaat
**
**  For more information visit the following website.
**  Website : www.plaatsoft.nl
**
**  Or send an email to the following address.
**  Email   : info@plaatsoft.nl
**
**  All copyrights reserved (c) PlaatSoft
*/

var mid;
var eid;

function facebookInit(mid, eid) {
	this.mid = mid;
	this.eid = eid;
}

function facebookURL() {
	var url = location.href;
	var baseURL = url.substring(0, url.indexOf('/', 14));

	if (baseURL.indexOf('http://127.0.0.1') != -1) {

		var url = location.href;
		var pathname = location.pathname;
		var index1 = url.indexOf(pathname);
		var index2 = url.indexOf("/", index1 + 1);
		var baseLocalUrl = url.substr(0, index2);

		return baseLocalUrl + "/";

	} else {

		return baseURL + "/";
	}
}

function facebookCall() {

	if (window.XMLHttpRequest) {
		// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	} else {
		// code for IE6, IE5
		xmlhttp=new ActiveXObject('Microsoft.XMLHTTP');
	}

	xmlhttp.open('POST',  facebookURL(), true);
	xmlhttp.setRequestHeader('Content-type','application/x-www-form-urlencoded');
	xmlhttp.send('mid='+mid+'&eid='+eid);
}
