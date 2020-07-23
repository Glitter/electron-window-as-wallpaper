# electron-window-as-wallpaper

A package for Electron that takes a BrowserWindow instance, and moves it to the wallpaper level

Note: It only works on Windows. It's installable on macOS and Linux as well, and can be called safely, but it will do nothing (you don't need to do any checks in your code for it)

## Installation

After installing this package locally, run `"./node_modules/.bin/electron-rebuild` - this will build the module against your current environment.

## Usage

Include the module:

```js
import { renderAsWallpaper } from '@glitter/electron-window-as-wallpaper';
// - or -
const { renderAsWallpaper } = require('@glitter/electron-window-as-wallpaper');
```

Then, after creating your BrowserWindow:

```js
const main = new BrowserWindow({
  // ...
});
```

Get the native window handle, and pass it to the function:

```js
const handle = main.getNativeWindowHandle();
const renderedAsWallpaper = renderAsWallpaper(handle);

console.log(renderedAsWallpaper); // true if it succeeded, false if not
```
