/* All copyrights reserved (c) 2008-2014 PlaatSoft */

function link(value)
{
	var form = document.forms['warquest'];
	var newInput = document.createElement('input');
	newInput.setAttribute('type','hidden');
	newInput.setAttribute('name','token');
	newInput.setAttribute('value',value);
	form.appendChild(newInput);		
		
	form.submit();
}

function show_confirm(question, token) 
{ 
	if (confirm(question)==true) 
	{
		link(token); 
	} 
}


