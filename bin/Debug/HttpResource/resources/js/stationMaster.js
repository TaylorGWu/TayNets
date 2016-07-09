$(document).ready(function()
{


});

function showMovieManage()
{
	$("#movieManage").show();
	$("#documentaryManage").hide();
	$("#othersManage").hide();
	$("#filmInfo").removeClass("active");
	$("#movieManageLink").addClass("active");
	$("#documentaryManageLink").removeClass("active");
	$("#othersManageLink").removeClass("active");

}

function showDocumentaryManage()
{
	$("#movieManage").hide();
	$("#documentaryManage").show();
	$("#othersManage").hide();
	$("#filmInfo").removeClass("active");
	$("#movieManageLink").removeClass("active");
	$("#documentaryManageLink").addClass("active");
	$("#othersManageLink").removeClass("active");	
}

function showOthersManage()
{
	$("#movieManage").hide();
	$("#documentaryManage").hide();
	$("#othersManage").show();
	$("#filmInfo").removeClass("active");
	$("#movieManageLink").removeClass("active");
	$("#documentaryManageLink").removeClass("active");
	$("#othersManageLink").addClass("active");	
}

function removeAMovie(movieIndex)
{
	$("#movie" + movieIndex).remove();
} 

function removeADocumentary(documentaryIndex)
{
	$("#documentary" + documentaryIndex).remove();
}

function removeAOthers(othersIndex)
{
	$("#others" + othersIndex).remove();
}  