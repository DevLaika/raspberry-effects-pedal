# Pedal-pi

## TODO
- [ ] Decide on UI workflow
- [ ] Create schematic
- [ ] Create PCB layout
- [ ] Order PCB and parts
- [ ] Solder PCB

## JSON Effect scheme
- Scalability
- Button adressability

.conf regex 1 seperate primary function types /(^\S+\n)(((  )+\S+)( \S+)*\n?)*/gm https://regex101.com/r/C5LljL/1
remove type and first 2 spaces /^\S+|^  /gm

/(?:^chains\n)(?:(?:(?:^(?:  )+)(?:\S+)(?:\n?))+)/gm

master.chains[0].effects[0]
  triggerAction
    startstop
master.chains[0].effects[2]
  toggleEnabled
master.chains[0].effects[3]
  toggleEnabled
master.chains[1].effects[0]
  toggleEnabled
master.chains[1].effects[1]
  toggleEnabled