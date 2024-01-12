# HotPot

A universal hot reloading tool for any project.

## Installation

Download a release or simply copile it yourself, it's super easy:

```sh
g++ main.cpp -o hotpot -Ofast
```

Move the executable into your `/bin` folder and you're done.

## Usage

```sh
hotpot -h
```

You can view all the possible flags with the `help` flag.

### Flags

- `-r,--run,--runner` - Set command to run on refresh.
    - Ex1: `... -r "g++ main.cpp; ./a.out" ...`
    - Ex2: `... --runner "npm start" ...`
    - Ex3: `... --run "python app.py" ...`
- `-e,--extension,--extensions` - Choose which file extensions are monitored.
    - Ex: `... -e "cpp,py,js,h" ...`
    - Default: `"c,cpp,h,hpp"`
- `-d,--dir,--directory` - Choose which directory is monitored.
    - Ex1: `... -d "./src" ...`
    - Ex2: `... -d "~/Dev/hotpot" ...`
    - Default: `"./"`

## Troubleshooting

Running intensive programs may result in poor detection.

Press `Ctrl + C` after saving all changes to break the stuck cycle.
