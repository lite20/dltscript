if walking && falling -> stop
after walking
|> dance -> stop
|> play_music -> mute

if walking:
unless() then run, jump, skip;
twirl, [jump or skip], [[jump or skip] or [jump and skip]];

if walking:
> dance, [dead ? stop : jump]
> play music, mute
