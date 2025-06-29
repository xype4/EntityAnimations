Scriptname HOH_AltarOnHit extends ObjectReference  

Event OnHit(ObjectReference akAggressor, Form akSource, Projectile akProjectile, bool abPowerAttack, bool abSneakAttack, bool abBashAttack, bool abHitBlocked)

if da10.GetStage() == 52

    if n<4

rocks2.enable()
rocks2.activate(PlayerRef)

        n+=1

    else

da10.SetStage(53)
DA10RessurectBlurAnimated.Apply()
Utility.Wait(0.5)
Mace.Disable()
brokenaltar.enable()
self.disable()
int sound1 = destroyed.Play(playerref)
Sound.SetInstanceVolume(sound1, 1)
DA10RessurectBlurAnimated.Remove()

;DA10SummonValorTargetFX.play(Mace, 10)

int sound2 = rumble.Play(playerref)
Sound.SetInstanceVolume(sound2, 1)

Utility.Wait(0.85)
rocks.enable()
rocks.activate(PlayerRef)

endif
endif
endevent

int n

actor property playerref auto
objectreference property brokenaltar auto
objectreference property rocks auto
objectreference property rocks2 auto

Quest Property DA10 Auto
objectreference property Mace auto
VisualEffect Property DA10SummonValorTargetFX  Auto  
ImageSpaceModifier Property DA10RessurectBlurAnimated  Auto  
sound property destroyed auto
sound property rumble auto