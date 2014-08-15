
// remote control buttons
P(reach_upper_ls_button) =
	"<button type='button' class='btn btn-success btn-lg' onclick='moveToUpperLimitSwitch();'>"
		"Reach upper limit switch <span class='glyphicon glyphicon-chevron-up'></span>"
	"</button>"
	;

P(reach_lower_ls_button) =
	"<button type='button' class='btn btn-success btn-lg' onclick='moveToLowerLimitSwitch();'>"
		"Reach lower limit switch <span class='glyphicon glyphicon-chevron-down'></span>"
	"</button>"
;

P(reach_active_water_sensor_button) =
	"<button type='button' class='btn btn-warning btn-lg' onclick='reachActiveWaterSensor();'>"
		"Reach active water sensor"
	"</button>"
;

P(control_at_active_water_sensor_button) =
	"<button type='button' class='btn btn-warning btn-lg' onclick='controlVlonderOnActiveWaterSensor();'>"
		"Control vlonder"
	"</button>"
;

P(reach_and_control_at_active_water_sensor_button) =
	"<button type='button' class='btn btn-warning btn-lg' onclick='reachAndControlVlonderOnActiveWaterSensor();'>"
		"Reach and control vlonder"
	"</button>"
;


P(stop_button) =
	"<button type='button' class='btn btn-danger btn-lg' onclick='stop();'>"
		"STOP"
	"</button>"
;

P(water_sensor_dropdown_button) =
	"<div class='btn-group'>"
		"<button type = 'button' class = 'btn btn-info btn-lg dropdown-toggle' data-toggle = 'dropdown'>"
			"Select water sensor <span class = 'caret'></span>"
		"</button>"
		"<ul class = 'dropdown-menu' role = 'menu'>"
			"<li><a onclick='highBoatSensor();'>High boat sensor</a></li>"
			"<li><a onclick='lowBoatSensor();'>Low boat sensor</a></li>"
			"<li class = 'divider'></li>"
			"<li><a onclick='underWaterSensor();'>Under water sensor</a></li>"
		"</ul>"
	"</div>"
;


// nav bar

P(nav_bar) =
	"<nav class='navbar navbar-inverse navbar-default navbar-static-top' role='navigation'>"
		"<div class='container-fluid'>"
			"<div class='navbar-header'>"
				"<button type='button' class='navbar-toggle' data-toggle='collapse' data-target='#bs-example-navbar-collapse-1'>"
					"<span class = 'sr-only'>Toggle navigation</span>"
					"<span class = 'icon-bar'></span>"
					"<span class = 'icon-bar'></span>"
					"<span class = 'icon-bar'></span>"
				"</button>"
				"<a class='navbar-brand' href='#'>Platform</a>"
			"</div>"

			"<div class = 'collapse navbar-collapse' id = 'bs-example-navbar-collapse-1'>"
				"<ul class = 'nav navbar-nav'>"
					"<li class='active'><a data-toggle='tab' href = '#Tab-RemoteControl'>Remote Control</a></li>"
					"<li><a data-toggle='tab' href = '#Tab-Information'>Information</a></li>"
				"</ul>"
			"</div>"
		"</div>"
	"</nav>"
;

P(alert) = 
	"<div id='AjaxAlert' class='hide alert alert-danger' role='alert'>"
		"<strong>Warning!</strong> Better check yourself, you're not looking too good."
	"</div>"
	;

// html head and scripts

P(htmlHead) =
	"<html>"
		"<head>"
			"<meta name = 'viewport' content = 'width=device-width, initial-scale=1'/>"

			"<title>Arduino platform web control</title>"

			"<link rel=\"stylesheet\" href=\"//maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css\"/>"
			"<link rel=\"stylesheet\" href=\"//maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap-theme.min.css\"/>"

			"<script src='http://ajax.googleapis.com/ajax/libs/jquery/1.11.1/jquery.min.js'></script>"
			"<script src=\"//maxcdn.bootstrapcdn.com/bootstrap/3.2.0/js/bootstrap.min.js\"></script>"

			"<script>"

				"var ajaxTimer = setInterval(updateInformation, 2000);"

				"function stopTimer() {"
					"clearInterval(ajaxTimer);"
					"$('#stopstartTimerButton').removeAttr('onclick').attr('onclick', 'startTimer()');"
					"$('#stopstartTimerButton').html('Start Ajax timer');"
					"$('#stopstartTimerButton').removeClass('btn-danger').addClass('btn-success');"

					"$('#manualUpdateButton').removeClass('hide');"
				"}"

				"function startTimer() {"
					"ajaxTimer = setInterval(updateInformation, 2000);"
					"$('#stopstartTimerButton').removeAttr('onclick').attr('onclick', 'stopTimer()');"
					"$('#stopstartTimerButton').html('Stop Ajax timer');"
					"$('#stopstartTimerButton').removeClass('btn-success').addClass('btn-danger');"

					"$('#manualUpdateButton').addClass('hide');"
				"}"

				"function updateInformation() {"
					"$.ajax({"
						"type: 'GET',"
						"url: 'http://192.168.215.177/json',"
						"timeout: 1000,"

						"success: function(data, textStatus, jqXHR) {"
							"$('#AjaxAlert').hide();"
							"var json = $.parseJSON(jqXHR.responseText);"
							"updateVlonderMovingIcon(json.vlonder.moving_state);"
							"updateActiveWaterSensor(json.vlonder.active_water_sensor);"
						"},"

						"error: function(jqXHR, textStatus, errorThrown) {"
							"$('#AjaxAlert').html('<strong>Warning!</strong>' + ' There was an error when requesting the json data: ' + errorThrown);"
							"$('#AjaxAlert').removeClass('hide').show();"
						"}"
					"});"
				"}"

				"function updateActiveWaterSensor(water_sensor_name) {"
					"$('#active_water_sensor').text(water_sensor_name);"
				"}"

				"function updateVlonderMovingIcon(moving_state) {"
					"$('#vlonder_moving_icon').removeClass('glyphicon-chevron-up').removeClass('glyphicon-chevron-down').removeClass('glyphicon-minus');"
					"switch (moving_state) {"
						"case 2:"// vlonder_moving_down
							"$('#vlonder_moving_icon').addClass('glyphicon-chevron-down');"
							"break;"
						"case 1:"// vlonder_moving_up
							"$('#vlonder_moving_icon').addClass('glyphicon-chevron-up');"
							"break;"
						"case 0:"// vlonder_stopped
							"default:"
							"$('#vlonder_moving_icon').addClass('glyphicon-minus');"
					"}"
				"}"



				"function sendProgramStatePost(state) {"
					"$.post('http://192.168.215.177/web_control', 'program_state=' + state, '', '');"
				"}"

				

				"function sendWaterSensorPost(sensor) {"
					"$.post('http://192.168.215.177/web_control', 'water_sensor=' + sensor, '', '');"
				"}"

				"function reachActiveWaterSensor() {"
					"sendProgramStatePost(1);"
				"}"

				"function reachAndControlVlonderOnActiveWaterSensor() {"
					"sendProgramStatePost(2);"
				"}"

				"function controlVlonderOnActiveWaterSensor() {"
					"sendProgramStatePost(3);"
				"}"

				"function moveToUpperLimitSwitch() {"
					"sendProgramStatePost(4);"
				"}"

				"function moveToLowerLimitSwitch() {"
					"sendProgramStatePost(5);"
				"}"

				"function stop() {"
					"sendProgramStatePost(0);"
				"}"

				"document.onkeydown = checkKey;"

				"function checkKey(e) {"
					"e = e || window.event;"
					"if (e.keyCode == '38')			moveToUpperLimitSwitch();"
					"else if (e.keyCode == '40')	moveToLowerLimitSwitch();"
					"else if (e.keyCode == '27')	stop();"
				"}"

				"function highBoatSensor() {"
					"sendWaterSensorPost(0);"
				"}"

				"function lowBoatSensor() {"
					"sendWaterSensorPost(1);"
				"}"

				"function underWaterSensor() {"
					"sendWaterSensorPost(2);"
				"}"

			"</script>"
		"</head>"
	"<body>"
		


		
		
;