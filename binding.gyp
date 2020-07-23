{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "electron-window-as-wallpaper",
      "sources": [],
      "conditions": [
        ['OS=="win"', {'sources':['lib.cc']},  { "sources": ["none.cc"] }],
      ]
    }
  ]
}
