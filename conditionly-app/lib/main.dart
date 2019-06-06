import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:myapp/theme.dart' as Theme;

void main() => runApp(new MyApp());

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: 'Conditionly Demo',
      theme: new ThemeData(
        // This is the theme of your application.
        //
        // Try running your application with "flutter run". You'll see the
        // application has a blue toolbar. Then, without quitting the app, try
        // changing the primarySwatch below to Colors.green and then invoke
        // "hot reload" (press "r" in the console where you ran "flutter run",
        // or press Run > Flutter Hot Reload in IntelliJ). Notice that the
        // counter didn't reset back to zero; the application is not restarted.
        primarySwatch: Colors.blue,
      ),
      home: new MyHomePage(title: 'Conditionly'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  // This widget is the home page of your application. It is stateful, meaning
  // that it has a State object (defined below) that contains fields that affect
  // how it looks.

  // This class is the configuration for the state. It holds the values (in this
  // case the title) provided by the parent (in this case the App widget) and
  // used by the build method of the State. Fields in a Widget subclass are
  // always marked "final".

  final String title;

  @override
  _MyHomePageState createState() => new _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  int _tmp = 22;
  int _mode = 0;
  int _fan = 0;
  bool _power = false;
  bool _swing = false;
  bool _swingLR = false;

  static const platform = const MethodChannel('samples.flutter.io/iot');
  final GlobalKey<ScaffoldState> _scaffoldKey = new GlobalKey<ScaffoldState>();
  final snackBar = SnackBar(content: Text('Command sent'));
  // Temperature
  void _incrementTmp() {
    // This call to setState tells the Flutter framework that something has
    // changed in this State, which causes it to rerun the build method below
    // so that the display can reflect the updated values. If we changed
    // _counter without calling setState(), then the build method would not be
    // called again, and so nothing would appear to happen.
    setState(() {

      _tmp++;

      if (_tmp > 32) {
        _tmp = 32;
      }
    });
  }

  void _decrementTmp() {
    setState(() {
      _tmp--;
      if (_tmp < 18) {
        _tmp = 18;
      }
    });
  }

  // Mode
  void _incrementMode() {
    setState(() {

      _mode++;

      if (_mode > 4) {
        _mode = 4;
      }
    });
  }

  void _decrementMode() {
    setState(() {
      _mode--;
      if (_mode < 0) {
        _mode = 0;
      }
    });
  }

  // Fan
  void _incrementFan() {
    setState(() {

      _fan++;

      if (_fan > 6) {
        _fan = 6;
      }
    });
  }

  void _decrementFan() {
    setState(() {
      _fan--;
      if (_fan < 0) {
        _fan = 0;
      }
    });
  }

  // Power
  void _switchPower() {
    setState(() {

      _power = !_power;

    });
  }

  // Swing
  void _switchSwing() {
    setState(() {

      _swing = !_swing;

    });
  }

  // SwingLR
  void _switchSwingLR() {
    setState(() {

      _swingLR = !_swingLR;

    });
  }

  //Send data to AWS IoT
  void _publishToCond() {

    platform.invokeMethod('publishToDevice', <String, dynamic>{
      'power': _power,
      'mode': _mode,
      'fan': _fan,
      'swing': _swing,
      'swingLR': _swingLR,
      'temp': _tmp
    });
    _scaffoldKey.currentState.showSnackBar(snackBar);

  }

  @override
  Widget build(BuildContext context) {
    // This method is rerun every time setState is called, for instance as done
    // by the _incrementCounter method above.
    //
    // The Flutter framework has been optimized to make rerunning build methods
    // fast, so that you can just rebuild anything that needs updating rather
    // than having to individually change instances of widgets.
    return new Scaffold(
      key: _scaffoldKey,
      appBar: new AppBar(
        // Here we take the value from the MyHomePage object that was created by
        // the App.build method, and use it to set our appbar title.
        title: new Text(widget.title, style: TextStyle(
            color: Colors.white,
            fontSize: 24.0,
            fontFamily: "WorkSansSemiBold"),),
        backgroundColor: Theme.Colors.loginGradientEnd,
        centerTitle: true,
      ),
      body: new Center(
        // Center is a layout widget. It takes a single child and positions it
        // in the middle of the parent.
        child: new Container(
         padding: EdgeInsets.all(30.0),
          width: MediaQuery.of(context).size.width,
          height: MediaQuery.of(context).size.height,
          decoration: new BoxDecoration(
            gradient: new LinearGradient(
                colors: [
                  Theme.Colors.loginGradientEnd,
                  Theme.Colors.loginGradientStart
                ],
                begin: const FractionalOffset(0.0, 0.0),
                end: const FractionalOffset(1.0, 1.0),
                stops: [0.0, 1.0],
                tileMode: TileMode.clamp),
          ),
          child: Column(mainAxisAlignment: MainAxisAlignment.spaceBetween, children: <Widget>[
            new Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: <Widget>[
                new Row(children: <Widget>[
                  new Text(
                    'Power: ',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 26.0,
                        fontFamily: "WorkSansSemiBold"),
                    textAlign: TextAlign.left,
                  ),
                  new Text(
                    '$_power',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 26.0,
                        fontFamily: "WorkSansSemiBold",
                        fontWeight: FontWeight.bold),
                    textAlign: TextAlign.left,
                  ),
                ],),
                new Row(children: <Widget>[
                  Switch(
                    value: _power,
                    onChanged: (value) {
                      setState(() {
                        _power = value;
                      });
                    },

                  ),
                ],),
              ],
            ),
            new Row(
              // Column is also layout widget. It takes a list of children and
              // arranges them vertically. By default, it sizes itself to fit its
              // children horizontally, and tries to be as tall as its parent.
              //
              // Invoke "debug paint" (press "p" in the console where you ran
              // "flutter run", or select "Toggle Debug Paint" from the Flutter tool
              // window in IntelliJ) to see the wireframe for each widget.
              //
              // Column has various properties to control how it sizes itself and
              // how it positions its children. Here we use mainAxisAlignment to
              // center the children vertically; the main axis here is the vertical
              // axis because Columns are vertical (the cross axis would be
              // horizontal).
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: <Widget>[
                new Row(children: <Widget>[
                  new Text(
                    'Temperature: ',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 26.0,
                        fontFamily: "WorkSansSemiBold"),
                    textAlign: TextAlign.left,
                  ),
                  new Text(
                    '$_tmp',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 26.0,
                        fontFamily: "WorkSansSemiBold",
                        fontWeight:  FontWeight.bold),
                    textAlign: TextAlign.left,
                  ),
                ],),
                new Row(children: <Widget>[
                  new FloatingActionButton(
                    onPressed: _decrementTmp,
                    tooltip: '-1',
                    mini: true,
                    backgroundColor: Theme.Colors.loginGradientEnd,
                    child: new Text('-'),
                  ),
                  new FloatingActionButton(
                    onPressed: _incrementTmp,
                    tooltip: '+1',
                    mini: true,
                    backgroundColor: Theme.Colors.loginGradientEnd,
                    child: new Text('+'),
                  )
                ],),
              ],
            ),
            new Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: <Widget>[
                new Row(children: <Widget>[
                  new Text(
                    'Fan: ',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 26.0,
                        fontFamily: "WorkSansSemiBold"),
                    textAlign: TextAlign.left,
                  ),
                  new Text(
                    '$_fan',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 26.0,
                        fontFamily: "WorkSansSemiBold",
                        fontWeight:  FontWeight.bold),
                    textAlign: TextAlign.left,
                  ),
                ],),
                new Row(children: <Widget>[
                  Text("Select", style: TextStyle(
                      color: Colors.white,
                      fontSize: 18.0,
                      fontFamily: "WorkSansSemiBold"),),
                  PopupMenuButton<int>(
                    icon: Icon(Icons.arrow_drop_down),
                    onSelected: (int result) { setState(() { _fan = result; }); },
                    itemBuilder: (BuildContext context) => <PopupMenuEntry<int>>[
                      const PopupMenuItem(
                        value: 0,
                        child: Text('FAN'),
                      ),
                      const PopupMenuItem(
                        value: 1,
                        child: Text('COOL'),
                      ),
                      const PopupMenuItem(
                        value: 2,
                        child: Text('DRY'),
                      ),
                      const PopupMenuItem(
                        value: 3,
                        child: Text('HEAT'),
                      ),
                      const PopupMenuItem(
                        value: 4,
                        child: Text('AUTO'),
                      ),
                    ],
                  ),
                ],),
              ],
            ),
            new Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: <Widget>[
                new Row(children: <Widget>[
                  new Text(
                    'Mode: ',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 26.0,
                        fontFamily: "WorkSansSemiBold"),
                    textAlign: TextAlign.left,
                  ),
                  new Text(
                    '$_mode',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 26.0,
                        fontFamily: "WorkSansSemiBold",
                    fontWeight: FontWeight.bold),
                    textAlign: TextAlign.left,
                  ),
                ],),
                new Row(children: <Widget>[
                  Text("Select", style: TextStyle(
                      color: Colors.white,
                      fontSize: 18.0,
                      fontFamily: "WorkSansSemiBold"),),
                  PopupMenuButton<int>(
                    icon: Icon(Icons.arrow_drop_down),
                    onSelected: (int result) { setState(() { _mode = result; }); },
                    itemBuilder: (BuildContext context) => <PopupMenuEntry<int>>[
                      const PopupMenuItem(
                        value: 0,
                        child: Text('SPEED 1'),
                      ),
                      const PopupMenuItem(
                        value: 1,
                        child: Text('SPEED 2'),
                      ),
                      const PopupMenuItem(
                        value: 2,
                        child: Text('SPEED 3'),
                      ),
                      const PopupMenuItem(
                        value: 3,
                        child: Text('SPEED 4'),
                      ),
                      const PopupMenuItem(
                        value: 4,
                        child: Text('SPEED 5'),
                      ),
                      const PopupMenuItem(
                        value: 5,
                        child: Text('AUTO'),
                      ),
                      const PopupMenuItem(
                        value: 6,
                        child: Text('NIGHT MODE'),
                      ),
                    ],
                  ),
                ],),
              ],
            ),
            new Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: <Widget>[
                new Row(children: <Widget>[
                  new Text(
                    'Swing: ',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 26.0,
                        fontFamily: "WorkSansSemiBold"),
                    textAlign: TextAlign.left,
                  ),
                  new Text(
                    '$_swing',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 26.0,
                        fontFamily: "WorkSansSemiBold",
                        fontWeight: FontWeight.bold),
                    textAlign: TextAlign.left,
                  ),
                ],),
                new Row(children: <Widget>[
                  Switch(
                    value: _swing,
                    onChanged: (value) {
                      setState(() {
                        _swing = value;
                      });
                    },
                  ),
                ],),
              ],
            ),
            new Row(
              mainAxisAlignment: MainAxisAlignment.spaceBetween,
              children: <Widget>[
                new Row(children: <Widget>[
                  new Text(
                    'SwingLR: ',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 26.0,
                        fontFamily: "WorkSansSemiBold"),
                    textAlign: TextAlign.left,
                  ),
                  new Text(
                    '$_swingLR',
                    style: TextStyle(
                        color: Colors.white,
                        fontSize: 26.0,
                        fontFamily: "WorkSansSemiBold",
                        fontWeight: FontWeight.bold),
                    textAlign: TextAlign.left,
                  ),
                ],),
                new Row(children: <Widget>[
                  Switch(
                    value: _swingLR,
                    onChanged: (value) {
                      setState(() {
                        _swingLR = value;
                      });
                    },
                  ),
                ],),
              ],
            ),
            new Divider(),
            new Row(
              crossAxisAlignment: CrossAxisAlignment.center,
              mainAxisAlignment: MainAxisAlignment.center,

              children: <Widget>[
                new RaisedButton(
                  onPressed: _publishToCond,
                  child: new Text('SEND COMMAND', style: TextStyle(fontSize: 18.0, color: Colors.white)),
                  color: Theme.Colors.loginGradientEnd,
                  padding: EdgeInsets.symmetric(horizontal: 25.0, vertical: 16.0), // gives padding to the button),
                ),
              ],
            ),
          ],),
        ),
      ),
    );
  }
}
