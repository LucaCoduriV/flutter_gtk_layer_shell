import 'dart:io';
import 'dart:ui';

import 'package:flutter/services.dart';

import 'channels.dart';
import 'layer_shell_controller.dart';

class LayerShellControllerMainImpl extends LayerShellController {
  final MethodChannel _channel = multiWindowChannel;

  // the id of this window
  final int _id;

  LayerShellControllerMainImpl(this._id);

  @override
  int get windowId => _id;

  @override
  Future<void> close() {
    return _channel.invokeMethod('close', _id);
  }

  @override
  Future<void> hide() {
    return _channel.invokeMethod('hide', _id);
  }

  @override
  Future<void> show() {
    return _channel.invokeMethod('show', _id);
  }

  @override
  Future<void> center() {
    return _channel.invokeMethod('center', _id);
  }

  @override
  Future<void> setFrame(Rect frame) {
    return _channel.invokeMethod('setFrame', <String, dynamic>{
      'windowId': _id,
      'left': frame.left,
      'top': frame.top,
      'width': frame.width,
      'height': frame.height,
    });
  }

  @override
  Future<void> setTitle(String title) {
    return _channel.invokeMethod('setTitle', <String, dynamic>{
      'windowId': _id,
      'title': title,
    });
  }

  @override
  Future<void> resizable(bool resizable) {
    if (Platform.isMacOS) {
      return _channel.invokeMethod('resizable', <String, dynamic>{
        'windowId': _id,
        'resizable': resizable,
      });
    } else {
      throw MissingPluginException(
        'This functionality is only available on macOS',
      );
    }
  }

  @override
  Future<void> setFrameAutosaveName(String name) {
    return _channel.invokeMethod('setFrameAutosaveName', <String, dynamic>{
      'windowId': _id,
      'name': name,
    });
  }

  @override
  Future<bool> autoExclusiveZoneIsEnabled() {
    // TODO: implement autoExclusiveZoneIsEnabled
    throw UnimplementedError();
  }

  @override
  Future<void> enableExclusiveZone() {
    // TODO: implement enableExclusiveZone
    throw UnimplementedError();
  }

  @override
  Future<bool> getAnchor(LayerEdge edge) {
    // TODO: implement getAnchor
    throw UnimplementedError();
  }

  @override
  Future<int> getExclusiveZone() {
    // TODO: implement getExclusiveZone
    throw UnimplementedError();
  }

  @override
  Future<bool> getKeyboardInteractivity(bool interactivity) {
    // TODO: implement getKeyboardInteractivity
    throw UnimplementedError();
  }

  @override
  Future<LayerShellKeyboardMode> getKeyboardMode() {
    // TODO: implement getKeyboardMode
    throw UnimplementedError();
  }

  @override
  Future<LayerSurface> getLayer() {
    // TODO: implement getLayer
    throw UnimplementedError();
  }

  @override
  Future<int> getMargin(LayerEdge edge) {
    // TODO: implement getMargin
    throw UnimplementedError();
  }

  @override
  Future<void> setAnchor(LayerEdge edge, bool anchor) {
    // TODO: implement setAnchor
    throw UnimplementedError();
  }

  @override
  Future<void> setExclusiveZone(int size) {
    // TODO: implement setExclusiveZone
    throw UnimplementedError();
  }

  @override
  Future<void> setKeyboardInteractivity(bool interactivity) {
    // TODO: implement setKeyboardInteractivity
    throw UnimplementedError();
  }

  @override
  Future<void> setKeyboardMode(LayerShellKeyboardMode mode) {
    // TODO: implement setKeyboardMode
    throw UnimplementedError();
  }

  @override
  Future<void> setLayer(LayerSurface layer) {
    // TODO: implement setLayer
    throw UnimplementedError();
  }

  @override
  Future<void> setMargin(LayerEdge edge, int margin) {
    // TODO: implement setMargin
    throw UnimplementedError();
  }
}
