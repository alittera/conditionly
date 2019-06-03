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

    private val client: AWSIotMqttClient by lazy { connectToAws() }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        GeneratedPluginRegistrant.registerWith(this)

        MethodChannel(flutterView, CHANNEL).setMethodCallHandler { call, result ->
            if (call.method == "publishToDevice") {
                publish(call.argument("payload")!!)
                result.success(true)
            } else {
                result.notImplemented()
            }
        }
    }

    fun connectToAws(): AWSIotMqttClient {
        Log.d(TAG, "connect")
        val client = AWSIotMqttClient("a3knmvk82jtze4-ats.iot.us-east-2.amazonaws.com", "123", "access-key", "access-password")
        client.connect()
        Log.d(TAG, client.getConnectionStatus().toString())
        return client
    }

    fun publish(payload: String) {
        val rootObject= JSONObject()
        rootObject.put("message",payload)
        val msg = MyMessage(topic, AWSIotQos.QOS0, rootObject.toString())
        client.publish(msg, 3000)
    }
}
