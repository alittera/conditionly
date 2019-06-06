package com.example.myapp

import com.amazonaws.services.iot.client.AWSIotException
import com.amazonaws.services.iot.client.AWSIotMqttClient
import com.amazonaws.services.iot.client.AWSIotQos
import com.amazonaws.services.iot.client.AWSIotMessage

import android.os.Bundle
import android.util.Log

import io.flutter.plugin.common.MethodChannel
import io.flutter.app.FlutterActivity
import io.flutter.plugins.GeneratedPluginRegistrant
import org.json.JSONObject



class MyMessage(topic: String, qos: AWSIotQos, payload: String) : AWSIotMessage(topic, qos, payload) {

    override fun onSuccess() {
        // called when message publishing succeeded
    }

    override fun onFailure() {
        // called when message publishing failed
    }

    override fun onTimeout() {
        // called when message publishing timed out
    }
}

class MainActivity() : FlutterActivity() {
    private val CHANNEL = "samples.flutter.io/iot"

    private val TAG = "DEBUG"
    private val topic = "conditionly/message"
    private var id:Int = 0;

    private val client: AWSIotMqttClient by lazy { connectToAws() }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        GeneratedPluginRegistrant.registerWith(this)

        MethodChannel(flutterView, CHANNEL).setMethodCallHandler { call, result ->
            if (call.method == "publishToDevice") {
               /* val payload = call.argument<Map<String, String>>("command");*/
                val rootObject= JSONObject()
                rootObject.put("id",id as Int)
                rootObject.put("power", call?.argument<Boolean>("power") as Boolean)
                rootObject.put("mode", call?.argument<Int>("mode") as Int)
                rootObject.put("fan", call?.argument<Int>("fan") as Int)
                rootObject.put("swing", call?.argument<Boolean>("swing") as Boolean)
                rootObject.put("swingLR", call?.argument<Boolean>("swingLR") as Boolean)
                rootObject.put("temp", call?.argument<Int>("temp") as Int)
                publish(rootObject!!)
                result.success(true)
                id++
            } else {
                result.notImplemented()
            }
        }
    }


    fun connectToAws(): AWSIotMqttClient {
        Log.d(TAG, "connect")
        val client = AWSIotMqttClient("a3knmvk82jtze4-ats.iot.us-east-2.amazonaws.com", "123", "AKIAIDSAT653LMNPZ4RQ", "Q2M8urfOPcbmTlSnje+aS3/fRiC1slapZC0EV+9d")
        client.connect()
        Log.d(TAG, client.getConnectionStatus().toString())
        return client
    }

    fun publish(payload: JSONObject) {
        val msg = MyMessage(topic, AWSIotQos.QOS0, payload.toString())
        client.publish(msg, 3000)
    }
}
