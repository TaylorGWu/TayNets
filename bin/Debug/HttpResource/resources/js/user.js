var currentPage = "movie";
$(document).ready(function(){


});

function movieShow() 
{
	currentPage = "movie";
	$("#movie").show();
	$("#documentary").hide();
	$("#others").hide();
	$("#myInfo").hide();
	$("#filmDetail").hide();
	$("#movieLink").addClass("active");
	$("#documentaryLink").removeClass("active");
	$("#othersLink").removeClass("active");
	$("#myInfoLink").removeClass("active");
	/*document.getElementById("movie").style.display = "";
	document.getElementById("documentary").style.display = "none";*/

}

function documentaryShow()
{
	currentPage = "documentary";
	$("#movie").hide();
	$("#documentary").show();
	$("#others").hide();
	$("#myInfo").hide();
	$("#filmDetail").hide();
	$("#movieLink").removeClass("active");
	$("#documentaryLink").addClass("active");
	$("#othersLink").removeClass("active");
	$("#myInfoLink").removeClass("active");
	/*document.getElementById("movie").style.display = "none";
	document.getElementById("documentary").style.display = "";	*/
}

function othersShow()
{
	currentPage = "others";
	$("#movie").hide();
	$("#documentary").hide();
	$("#others").show();
	$("#myInfo").hide();
	$("#filmDetail").hide();
	$("#movieLink").removeClass("active");
	$("#documentaryLink").removeClass("active");
	$("#othersLink").addClass("active");
	$("#myInfoLink").removeClass("active");

}

function myInfoShow()
{
	$("#movie").hide();
	$("#documentary").hide();
	$("#others").hide();
	$("#myInfo").show();
	$("#filmDetail").hide();
	$("#movieLink").removeClass("active");
	$("#documentaryLink").removeClass("active");
	$("#othersLink").removeClass("active");
	$("#myInfoLink").addClass("active");
}

function goBack()
{
	if(currentPage == "movie")
		movieShow();
	else if(currentPage == "documentary")
		documentaryShow();
	else 
		othersShow();

}

function filmDetailShow(obj)
{
	$("#movie").hide();
	$("#documentary").hide();
	$("#others").hide();
	$("#myInfo").hide();
	$("#filmDetail").show();
}