function consultaGET(endpoint, cb) {
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (xhr.readyState === XMLHttpRequest.DONE) {
            if (cb) {
                var res = { "error": "true" };
                try {
                    if (xhr.status >= 200 && xhr.status < 300) {
                        res = JSON.parse(xhr.responseText.toString());
                    } else {
                        console.error("HTTP Error: " + xhr.status);
                    }
                } catch (e) {
                    if (e instanceof SyntaxError) {
                        console.error("SyntaxError: Unable to parse JSON string", e);
                    } else {
                        console.error("Error: ", e);
                    }
                }
                cb(res);
            }
        }
    };
    xhr.open("GET", endpoint, true);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.setRequestHeader('Accept', 'application/json');
    xhr.send();
}
