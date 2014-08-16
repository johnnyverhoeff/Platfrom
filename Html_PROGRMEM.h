
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

// table remote control buttons

P(table_remote_control_buttons) =
	"<table class='table table-striped table-condensed'>"
		"<tr>"
			"<th>Button</th>"
			"<th>Status "
				"<button onclick='tableCollapseButtonIcon()' class='btn btn-primary btn-xs collapsed pull-right' data-toggle='collapse' data-target='.collapse-able'>"
					"<span id='collapse_able_table_icon' class='glypicon glyphicon-plus'></span>"
				"</button>"
			"</th>"
		"</tr>"
		
		"<tr class='collapse out collapse-able'>"
			"<td>Button 0</td>"
			"<td id='button0_status'>false</td>"
		"</tr>"
		"<tr class='collapse out collapse-able'>"
			"<td>Button 1</td>"
			"<td id='button1_status'>false</td>"
		"</tr>"
		"<tr class='collapse out collapse-able'>"
			"<td>Button 2</td>"
			"<td id='button2_status'>false</td>"
		"</tr>"
		"<tr class='collapse out collapse-able'>"
			"<td>Button 3</td>"
			"<td id='button3_status'>false</td>"
		"</tr>"
		"<tr class='collapse out collapse-able'>"
			"<td>Button 4</td>"
			"<td id='button4_status'>false</td>"
		"</tr>"
		"<tr class='collapse out collapse-able'>"
			"<td>Button 5</td>"
			"<td id='button5_status'>false</td>"
		"</tr>"
		"<tr class='collapse out collapse-able'>"
			"<td>Button 6</td>"
			"<td id='button6_status'>false</td>"
		"</tr>"
		"<tr class='collapse out collapse-able'>"
			"<td>Button 7</td>"
			"<td id='button7_status'>false</td>"
		"</tr>"
	"</table>"

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


// alerts

P(alerts) = 
	"<div id='AjaxJsonAlert' class='hide alert alert-danger' role='alert'>"
		"<strong>Warning!</strong> Better check yourself, you're not looking too good."
	"</div>"

	"<div id='AjaxWaterAlert' class='hide alert alert-danger' role='alert'>"
		"<strong>Warning!</strong> Better check yourself, you're not looking too good."
	"</div>"

	"<div id='upperLimitSwitchAlert' class='hide alert alert-info' role='alert'>"
		"<strong>Heads up!</strong> Upper limit switch is reached."
	"</div>"

	"<div id='lowerLimitSwitchAlert' class='hide alert alert-info' role='alert'>"
		"<strong>Heads up!</strong> Lower limit switch is reached."
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

				"function updateJSONInformation() { "
					"$.ajax({"
						"type: 'GET',"
						"url: 'http://192.168.215.177/json',"
						"timeout: 2000,"

						"success: function(data, textStatus, jqXHR) {"
							"$('#AjaxJsonAlert').hide();"

							"var json = $.parseJSON(jqXHR.responseText);"

							"updateVlonderMovingIcon(json.vlonder.moving_state);"
							"updateActiveWaterSensor(json.vlonder.active_water_sensor);"
							"updateLimitSwitches(json.vlonder.upper_limit_switch, json.vlonder.lower_limit_switch);"
							"updateProgramState(json.program_state);"
							"updateButtonsTable(json.buttons);"
						"},"

						"error: function(jqXHR, textStatus, errorThrown) {"
							"$('#AjaxJsonAlert').html('<strong>Warning!</strong>' + ' There was an error when requesting the json data: ' + errorThrown);"
							"$('#AjaxJsonAlert').removeClass('hide').show();"
						"}"
					"});"
				"}"

				"function updateWaterMeasurerInformation() {"
					"$.ajax({"
						"type: 'GET',"
						"url: 'http://192.168.215.177/water_measurer',"
						"timeout: 5000,"

						"success: function(data, textStatus, jqXHR) {"
							"$('#AjaxWaterAlert').hide();"

							"var json = $.parseJSON(jqXHR.responseText);"

							"updateCurrentDecision(json);"
							
							"$('#remainingTimeSpan').text((json.total_samples - json.current_sample) * json.sample_time / 10 + ' s');"

							"$('#totalSamplesSpan').text(json.total_samples);"
							"$('#currentSampleSpan').text(json.current_sample);"
							"$('#droppingHitsSpan').text(json.water_dropping_hits);"
							"$('#risingHitsSpan').text(json.water_rising_hits);"

							"var percentage = 100 * json.current_sample / json.total_samples;"
							"updateProgressBars(percentage);"
							
						"},"

						"error: function(jqXHR, textStatus, errorThrown) {"
							"$('#AjaxWaterAlert').html('<strong>Warning!</strong>' + ' There was an error when requesting the water measurement data: ' + errorThrown);"
							"$('#AjaxWaterAlert').removeClass('hide').show();"
						"}"
					"});"
				"}"

				"function updateProgressBar(n, p) {"
					"var pbId = '#sampleProgressBar' + n;"
					"$(pbId).attr('style', 'width: ' + p + '%') ;"
				"}"

				"function updateProgressBars(percentage) {"
					"if (percentage <= 50) {"
						"updateProgressBar(1, percentage);"
						"updateProgressBar(2, 0);"
						"updateProgressBar(3, 0);"
					"} else if (percentage > 50 && percentage <= 75) {"
						"updateProgressBar(1, 50);"
						"updateProgressBar(2, percentage - 50);"
						"updateProgressBar(3, 0);"
					"} else if (percentage > 75) {"
					"updateProgressBar(1, 50);"
					"updateProgressBar(2, 25);"
					"updateProgressBar(3, percentage - 75);"
					"}"
				"}"

				"function updateCurrentDecision(json) {"
					"var water_rising_percentage = json.water_rising_hits * 100.0 / json.current_sample;\n"
					"var water_dropping_percentage = json.water_dropping_hits * 100.0 / json.current_sample;\n"

					"if (water_dropping_percentage <= json.lower_threshold && water_rising_percentage >= json.upper_threshold) \n" 
						"$('#currentDecisionSpan').removeClass('glyphicon-chevron-down').removeClass('glyphicon-minus').addClass('glyphicon-chevron-up');\n"
					
					"else if (water_dropping_percentage >= json.upper_threshold && water_rising_percentage <= json.lower_threshold) \n"
						"$('#currentDecisionSpan').removeClass('glyphicon-chevron-up').removeClass('glyphicon-minus').addClass('glyphicon-chevron-down');\n"

					"else \n"
						"$('#currentDecisionSpan').removeClass('glyphicon-chevron-down').removeClass('glyphicon-chevron-up').addClass('glyphicon-minus');\n"
				"}\n"

				"function updateInformation() {"
					"updateJSONInformation();"
					"updateWaterMeasurerInformation();"
				"}"

				"function updateButtonsTable(buttons) {"
					"for (var i = 0; i < 8; i++) {"
						"var buttonId = '#button' + i + '_status';"
						"var buttonState = buttons['Button' + i];"
						"$(buttonId).text(buttonState);"
					"}"
				"}"

				"function updateProgramState(state) {"
					"if (state === 3) "
						"$('#waterMeasurementPanel').removeClass('hide').show();"
					"else "
						"$('#waterMeasurementPanel').hide();"

					"switch (state) {"
						"case 1:"
							"$('#program_state').text('Reaching the active sensor');"
							"break;"
						"case 2:"
							"$('#program_state').text('Reaching than controlling at active sensor');"
							"break;"
						"case 3:"
							"$('#program_state').text('Controlling vlonder at active sensor');"
							"break;"
						"case 4:"
							"$('#program_state').text('Reaching upper limit switch');"
							"break;"
						"case 5:"
							"$('#program_state').text('Reaching lower limit switch');"
							"break;"
						"case 6:"
							"$('#program_state').text('Remote control manual up');"
							"break;"
						"case 7:"
							"$('#program_state').text('Remote control manual down');"
							"break;"
						"case 0:"
						"default:"
							"$('#program_state').text('none');"
							"break;"
					"}"
				"}"

				"function updateLimitSwitches(upper_ls, lower_ls) {"
					"if (upper_ls) "
						"$('#upperLimitSwitchAlert').removeClass('hide').show();"
					"else " 
						"$('#upperLimitSwitchAlert').hide();"

					"if (lower_ls) "
						"$('#lowerLimitSwitchAlert').removeClass('hide').show();"
					"else "
						"$('#lowerLimitSwitchAlert').hide();"
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

				"function tableCollapseButtonIcon() {"
					"if ($('#collapse_able_table_icon').hasClass('glyphicon-plus')) "
						"$('#collapse_able_table_icon').removeClass('glyphicon-plus').addClass('glyphicon-minus'); "
					"else "
						"$('#collapse_able_table_icon').removeClass('glyphicon-minus').addClass('glyphicon-plus');"
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

				"document.onkeydown = checkKeyDown;"
				"document.onkeyup = checkKeyUp;"
				
				"var keyPressed = false;"

				"function checkKeyUp(e) {"
					"var key = e.keyCode ? e.keyCode : e.which;"
					
					"if (key == '38' || key == '40') "
						"stop();"

					"keyPressed = false;"
				"}"
				
				"function checkKeyDown(e) {"
					"var key = e.keyCode ? e.keyCode : e.which;"
					
					"if (key == '27') "
						"stop();"

					"if (keyPressed) return; "
					
					"keyPressed = true;"

					"if (key == '38') "
						"moveToUpperLimitSwitch();"
					"else if (key == '40') "
						"moveToLowerLimitSwitch();"
					
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
