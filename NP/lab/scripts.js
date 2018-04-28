(function () {
	var audio = document.getElementById('audio');
	var audioControls = document.getElementById('audio-controls');
	var playpause = document.getElementById('playpause');
	var stop = document.getElementById('stop');
	var mute = document.getElementById('mute');
	var volinc = document.getElementById('volinc');
	var voldec = document.getElementById('voldec');
	var progress = document.getElementById('progress');
	var progressBar = document.getElementById('progress-bar');
	var title = document.getElementById('title');


	var changeButtonState = function(type) {
	   // Play/Pause button
	   if (type == 'playpause') {
		  if (audio.paused || audio.ended) {
			 playpause.setAttribute('data-state', 'play');
		  }
		  else {
			 playpause.setAttribute('data-state', 'pause');
		  }
	   } 
	   if (type == 'mute') {
		  mute.setAttribute('data-state', audio.muted ? 'unmute' : 'mute');
	   }
	}

	audio.addEventListener('play', function() {
	   changeButtonState('playpause');
	}, false);

	audio.addEventListener('pause', function() {
	   changeButtonState('playpause');
	}, false);

	stop.addEventListener('click', function(e) {
	   audio.pause();
	   audio.currentTime = 0;
	   progress.value = 0;
	   // Update the play/pause button's 'data-state' which allows the correct button image to be set via CSS
	   changeButtonState('playpause');
	});


	playpause.addEventListener('click', function(e) {
		if (audio.paused || audio.ended) audio.play();
		else audio.pause();
	});			

	mute.addEventListener('click', function(e) {
		audio.muted = !audio.muted;
		changeButtonState('mute');
	});
	volinc.addEventListener('click', function(e) {
		alterVolume('+');
	});
	voldec.addEventListener('click', function(e) {
		alterVolume('-');
	});

	var checkVolume = function(dir) {
	   if (dir) {
		  var currentVolume = Math.floor(audio.volume * 10) / 10;
		  if (dir === '+') {
			 if (currentVolume < 1) audio.volume += 0.1;
		  }
		  else if (dir === '-') {
			 if (currentVolume > 0) audio.volume -= 0.1;
		  }
		  // If the volume has been turned off, also set it as muted
		  // Note: can only do this with the custom control set as when the 'volumechange' event is raised, there is no way to know if it was via a volume or a mute change
		  if (currentVolume <= 0) audio.muted = true;
		  else audio.muted = false;
	   }
	   changeButtonState('mute');
	}
	var alterVolume = function(dir) {
	   checkVolume(dir);
	}

 	audio.addEventListener('loadedmetadata', function() {
		progress.setAttribute('max', audio.duration);
	});

	audio.addEventListener('timeupdate', function() {
		// For mobile browsers, ensure that the progress element's max attribute is set
		if (!progress.getAttribute('max')) progress.setAttribute('max', audio.duration);
		progress.value = audio.currentTime;
		progressBar.style.width = Math.floor((audio.currentTime / audio.duration) * 100) + '%';
	});

	progress.addEventListener('click', function(e) {
	   var pos = (e.pageX  - (this.offsetLeft + this.offsetParent.offsetLeft)) / this.offsetWidth;
	   audio.currentTime = pos * audio.duration;
	});

	function play_song(url, name) {
		audio.src = url;
		title.innerHTML = name;
        audio.play();
	    changeButtonState('playpause');
	}
    
    function play_song_bind(event) {
        var sname = this.getAttribute("sname");
        var surl = this.getAttribute("song");

        play_song(surl, sname);
    }

    function add_song(data) {
        var url = data.url;

        $("#song-list").append(
                "<li class ='song' sname='" + data.name + "' song='" +  url + "'>" + data.name + "</li>");
    }

    $.ajax({
        url: "http://127.0.0.1:5000/playlist", 
        type: 'GET',
        crossDomain: true,
        dataType: 'json',
        success: function(r) { 
            var d = r.data;
            for (i in d) {
                add_song(d[i]);
            } 
            $('.song').bind('click', play_song_bind);
        },
        error: function() { alert('Failed to load playlist!'); },
    });

})();
