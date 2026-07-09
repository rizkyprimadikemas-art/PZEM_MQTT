// ======================================================
// LANTABURA EMS
// WiFi Portal
// ======================================================

const wifiList = document.getElementById("wifiList");

const ssid = document.getElementById("ssid");

const password = document.getElementById("password");

const connectButton = document.getElementById("connectButton");

const statusBox = document.getElementById("status");

const mac = document.getElementById("mac");

const ip = document.getElementById("ip");

const connected = document.getElementById("connected");

const togglePassword = document.getElementById("togglePassword");



// ======================================================
// Init
// ======================================================

window.onload = function ()
{
    scanWifi();

    getStatus();

    setInterval(getStatus,5000);
}



// ======================================================
// Password
// ======================================================

togglePassword.onclick = function()
{
    if(password.type=="password")
    {
        password.type="text";
    }
    else
    {
        password.type="password";
    }
}



// ======================================================
// Status
// ======================================================

function setStatus(text,color="#334155")
{
    statusBox.innerHTML=text;

    statusBox.style.background=color;
}



// ======================================================
// Scan WiFi
// ======================================================

function scanWifi()
{
    wifiList.innerHTML="Scanning...";

    fetch("/scan")

    .then(response=>response.json())

    .then(data=>{

        wifiList.innerHTML="";

        if(data.length==0)
        {
            wifiList.innerHTML="No WiFi Found";

            return;
        }

        data.sort(function(a,b){

            return b.rssi-a.rssi;

        });

        data.forEach(item=>{

            const div=document.createElement("div");

            div.className="wifi-item";

            let level="low";

            if(item.rssi>-60)
                level="good";

            else if(item.rssi>-75)
                level="medium";

            div.innerHTML=

            "<div class='wifi-name'>"

            +item.ssid+

            "</div>"

            +

            "<div class='wifi-info "+level+"'>"

            +item.rssi+

            " dBm"

            +(item.secure?" 🔒":" 🔓")

            +"</div>";

            div.onclick=function(){

                ssid.value=item.ssid;

            };

            wifiList.appendChild(div);

        });

    })

    .catch(error=>{

        wifiList.innerHTML="Scan Failed";

    });

}
// ======================================================
// Save WiFi
// ======================================================

connectButton.onclick=function()
{

    if(ssid.value=="")
    {
        alert("SSID harus diisi");

        return;
    }

    setStatus(
        "Saving...",
        "#2563eb"
    );

    const body=

        "ssid="+

        encodeURIComponent(ssid.value)

        +

        "&password="+

        encodeURIComponent(password.value);

    fetch(

        "/save",

        {

            method:"POST",

            headers:{

                "Content-Type":

                "application/x-www-form-urlencoded"

            },

            body:body

        }

    )

    .then(response=>response.text())

    .then(data=>{

        setStatus(

            "ESP Restarting...",

            "#16a34a"

        );

    })

    .catch(error=>{

        setStatus(

            "Failed",

            "#dc2626"

        );

    });

}
// ======================================================
// Device Status
// ======================================================

function getStatus()
{

    fetch("/status")

    .then(response=>response.json())

    .then(data=>{

        mac.innerHTML=data.mac;

        ip.innerHTML=data.ip;

        connected.innerHTML=

            data.connected

            ?

            "YES"

            :

            "NO";

    })

    .catch(error=>{

    });

}