{
    "targets":[
        {
            "target_name": "prapra",
            "sources": ["src/library.cc"],
            "include_dirs": ["<!(node -e \"require('nan')\")"]
        }
    ]
}