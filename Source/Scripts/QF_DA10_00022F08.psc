;/ Decompiled by Champollion V1.0.1
Source   : QF_DA10_00022F08.psc
Modified : 2023-07-14 14:56:06
Compiled : 2023-07-14 14:56:07
User     : JJ
Computer : HAL9000
/;
scriptName QF_DA10_00022F08 extends Quest hidden

;-- Properties --------------------------------------
locationalias property Alias_Dungeon auto
furniture property BoundCaptiveMarker auto
scene property pTyranusForcegreetScene auto
key property pLogrolfHouse auto
locationalias property Alias_AbandonedHouse auto
scene property DA10StartScene auto
scene property DA10_NewScene auto
referencealias property Alias_PlayerRustyMace auto
scene property DA10LogrolfMolagBalScene03 auto
scene property DA10_Escape auto
imagespacemodifier property DA10ResurrectBlurAnimated auto
Quest property DA10HauntingController auto
scene property HouseTyranusScene02 auto
objectreference property MarkarthCenter auto
scene property pHouseHauntingScene auto
keyword property pHauntingKeyword auto
objectreference property DA10TyranusMarkerREF auto
referencealias property Alias_Logrolf auto
Quest property pDA10FIN auto
scene property MolagBalScene02 auto
scene property pTyranusFollowPlayer auto
scene property DA10EndScene auto
miscobject property Gold auto
faction property CrimeFactionReach auto
scene property pTyranusHouseScene01 auto
visualeffect property DA10ReanimateTargetFX auto
scene property AttachMachineScene auto
referencealias property Alias_RustyMaceTriggerREF auto
objectreference property DA10YngvarMarkerREF auto
idle property IdleCowerExit auto
referencealias property Alias_Altar auto
scene property pBasementDoorScene auto
objectreference property DA10NonStaticBedEnabler auto
locationalias property Alias_MarkarthLocation auto
scene property LogrolfMolagScene auto
referencealias property Alias_MapMarker auto
referencealias property Alias_MarkarthCenterMarker auto
faction property pCrimeFactionReach auto
idle property IdleExitFurniture auto
referencealias property Alias_MolagBalVoiceMarker auto
visualeffect property DA10SummonValorTargetFX auto
scene property DA10LogrolfMolagBalScene02 auto
referencealias property Alias_Tyranus auto
referencealias property Alias_DA10ReanimateCasterRef auto
scene property pMolagBalStatueScene01 auto
referencealias property Alias_AltarofMolagBal auto
referencealias property Alias_FriendlyVigilant auto
miscobject property TorturePlans auto
achievementsscript property AchievementsQuest auto
weapon property RustyMace auto
key property pBasementKey auto
weapon property DA10MaceofMolagBal auto
scene property pLogrolfHitScene auto
referencealias property Alias_RustyMaceIntRef auto
scene property pMainDoorScene auto
referencealias property Alias_MolagBalFinalTalking auto
objectreference property pBoethiahDoor auto
Quest property pHauntingQuest auto
referencealias property Alias_CaptiveMarker auto
referencealias property Alias_BasementDoor auto
referencealias property Alias_PlayerRustyMaceChest auto
referencealias property Alias_RustyMace auto
faction property pPlayerEnemyFaction auto
imagespacemodifier property DA10RessurectBlurAnimated auto
referencealias property Alias_MaceOfMolagBal auto
scene property pLogrolfForcegreetScene auto
referencealias property Alias_RustyMaceStatic auto
scene property pHouseEntryScene auto
referencealias property Alias_MainDoor auto
miscobject property pPainExtensor auto
referencealias property Alias_Yngvar auto
weapon property DA10RustyMace auto
scene property DA10LogrolfMolagBalScene01 auto

;-- Variables ---------------------------------------

;-- Functions ---------------------------------------

function Fragment_43()

	; Empty function
endFunction

function Fragment_77()

	; Empty function
endFunction

function Fragment_83()

	self.SetObjectiveCompleted(30, 1 as Bool)
	self.SetObjectiveDisplayed(35, 1 as Bool, false)
endFunction

function Fragment_79()

	; Empty function
endFunction

function Fragment_36()

	if self.GetStageDone(70) == 0 as Bool
		DA10HauntingController.SetStage(30)
	endIf
endFunction

; Skipped compiler generated GotoState

function Fragment_85()

	DA10LogrolfMolagBalScene03.Start()
endFunction

function Fragment_37()

	if self.GetStageDone(70) == 0 as Bool
		DA10HauntingController.SetStage(40)
	endIf
endFunction

function Fragment_72()

	actor pLogrolf = Alias_Logrolf.GetActorRef()
	DA10LogrolfMolagBalScene02.Start()
	Alias_Logrolf.GetActorRef().GetActorBase().SetEssential(true)
	DA10ResurrectBlurAnimated.Apply(1.00000)
	utility.Wait(1 as Float)
	DA10SummonValorTargetFX.play(pLogrolf as objectreference, 10 as Float, none)
	utility.Wait(0.500000)
	Alias_Logrolf.GetActorRef().Resurrect()
endFunction

function Fragment_62()

	self.SetObjectiveCompleted(35, 1 as Bool)
	self.SetObjectiveDisplayed(40, 1 as Bool, false)
	DA10LogrolfMolagBalScene01.Start()
endFunction

function Fragment_82()

	Alias_Altar.GetRef().PlayAnimation("Up")
endFunction

function Fragment_35()

	Alias_MainDoor.GetRef().Lock(true, false)
	Alias_Tyranus.GetActorRef().SetCrimeFaction(none)
	Alias_Tyranus.GetActorRef().RemoveFromFaction(CrimeFactionReach)
endFunction

function Fragment_40()

	if self.GetStageDone(70) == 0 as Bool
		DA10HauntingController.SetStage(10)
	endIf
	Alias_MainDoor.GetRef().Lock(true, false)
endFunction

function Fragment_41()

	; Empty function
endFunction

function Fragment_42()

	if self.GetStageDone(70) == 0 as Bool
		DA10HauntingController.SetStage(70)
	endIf
endFunction

function Fragment_86()

	Alias_Logrolf.GetActorRef().GetActorBase().SetEssential(false)
	self.SetObjectiveCompleted(50, 1 as Bool)
	self.SetObjectiveDisplayed(60, 1 as Bool, false)
endFunction

function Fragment_93()

	DA10_NewScene.Start()
	Alias_BasementDoor.GetRef().Lock(false, false)
	self.SetObjectiveCompleted(10, 1 as Bool)
	self.SetObjectiveDisplayed(11, true, false)
	Alias_Altar.GetRef().BlockActivation(true)
endFunction

function Fragment_84()

	self.SetObjectiveCompleted(40, 1 as Bool)
	self.SetObjectiveDisplayed(50, 1 as Bool, false)
	Alias_RustyMaceStatic.GetRef().Disable(false)
	Alias_MaceOfMolagBal.GetRef().Disable(false)
	game.GetPlayer().AddItem(Alias_PlayerRustyMace.GetRef() as form, 1, false)
	game.GetPlayer().EquipItem(DA10RustyMace as form, false, false)
endFunction

function Fragment_0()

	self.SetObjectiveDisplayed(10, 1 as Bool, false)
	Alias_Tyranus.GetActorRef().EvaluatePackage()
	pHouseEntryScene.Start()
	Alias_Tyranus.GetActorRef().GetActorBase().SetEssential(false)
	Alias_MainDoor.GetRef().Lock(false, false)
	Alias_Altar.GetRef().SetNoFavorAllowed(true)
	Alias_MaceOfMolagBal.GetRef().SetNoFavorAllowed(true)
	Alias_RustyMaceTriggerREF.GetRef().SetNoFavorAllowed(true)
endFunction

function Fragment_81()

	self.FailAllObjectives()
	self.Stop()
endFunction

function Fragment_80()

	Alias_MainDoor.GetRef().Lock(true, false)
	self.SetObjectiveFailed(10, 1 as Bool)
	self.Stop()
endFunction

function Fragment_75()

	; Empty function
endFunction

function Fragment_96()

	self.SetObjectiveCompleted(12, 1 as Bool)
	self.SetObjectiveDisplayed(13, true, false)
	DA10SummonValorTargetFX.play(Alias_MaceOfMolagBal.GetRef(), -1.00000, none)
	utility.Wait(0.100000)
	Alias_RustyMaceStatic.GetRef().Disable(false)
	Alias_MaceOfMolagBal.GetRef().Disable(false)
	Alias_Tyranus.GetActorRef().SetRelationshipRank(game.GetPlayer(), 3)
	DA10_Escape.Start()
endFunction

function Fragment_87()

	self.SetObjectiveCompleted(60, 1 as Bool)
	self.SetObjectiveDisplayed(70, 1 as Bool, false)
	Alias_Altar.GetRef().PlayAnimation("Down")
	while game.GetPlayer().GetEquippedWeapon(false) == DA10RustyMace
		game.GetPlayer().UnequipItem(DA10RustyMace as form, true, true)
		utility.Wait(1 as Float)
	endWhile
	game.GetPlayer().RemoveItem(DA10RustyMace as form, 1, false, none)
	game.GetPlayer().AddItem(DA10MaceofMolagBal as form, 1, false)
	game.GetPlayer().EquipItem(DA10MaceofMolagBal as form, false, false)
	AchievementsQuest.IncDaedricArtifacts()
	utility.Wait(1 as Float)
	Alias_MolagBalFinalTalking.GetRef().Activate(game.GetPlayer() as objectreference, false)
endFunction

function Fragment_54()

	Alias_Tyranus.GetActorRef().AddtoFaction(pPlayerEnemyFaction)
	Alias_Tyranus.GetActorRef().SendAssaultAlarm()
	Alias_Tyranus.GetActorRef().StartCombat(game.GetPlayer())
endFunction

function Fragment_88()

	; Empty function
endFunction

function Fragment_78()

	; Empty function
endFunction

function Fragment_76()

	Alias_MaceOfMolagBal.RegisterForUpdate(5 as Float)
endFunction

function Fragment_71()

	if self.GetStageDone(70) == 0 as Bool
		DA10HauntingController.SetStage(60)
	endIf
endFunction

function Fragment_92()

	Alias_Tyranus.GetActorRef().EvaluatePackage()
endFunction

function Fragment_90()

	AchievementsQuest.IncDaedricQuests()
	self.SetObjectiveCompleted(14, 1 as Bool)
	Alias_MainDoor.GetRef().Lock(false, false)
endFunction

function Fragment_89()

	Alias_Tyranus.GetActorRef().Enable(false)
	Alias_Tyranus.GetActorRef().Moveto(DA10TyranusMarkerREF, 0.000000, 0.000000, 0.000000, true)
	Alias_Yngvar.GetActorRef().EvaluatePackage()
	Alias_Yngvar.GetActorRef().Moveto(DA10YngvarMarkerREF, 0.000000, 0.000000, 0.000000, true)
	DA10StartScene.Start()
endFunction

function Fragment_39()

	pHauntingKeyword.SendStoryEvent(none, none, none, 0, 0)
endFunction

function Fragment_95()

	self.SetObjectiveCompleted(11, 1 as Bool)
	self.SetObjectiveDisplayed(12, true, false)
endFunction

; Skipped compiler generated GetState

function Fragment_97()

	self.SetObjectiveCompleted(13, 1 as Bool)
	self.SetObjectiveDisplayed(14, true, false)
	DA10HauntingController.SetStage(80)
	utility.Wait(0.500000)
	DA10HauntingController.SetStage(90)
	utility.Wait(0.500000)
	DA10HauntingController.SetStage(100)
	DA10_Escape.Stop()
endFunction

function Fragment_67()

	Alias_Yngvar.GetActorRef().EvaluatePackage()
endFunction

function Fragment_52()

	game.GetPlayer().StopCombatAlarm()
	DA10HauntingController.SetStage(80)
	self.SetObjectiveCompleted(10, 1 as Bool)
	self.SetObjectiveDisplayed(20, 1 as Bool, false)
	pMolagBalStatueScene01.Start()
	Alias_BasementDoor.GetRef().Lock(false, false)
endFunction

function Fragment_74()

	; Empty function
endFunction

function Fragment_55()

	Alias_MaceOfMolagBal.UnRegisterForUpdate()
	self.SetObjectiveCompleted(20, 1 as Bool)
	self.SetObjectiveDisplayed(30, 1 as Bool, false)
	game.EnablePlayerControls(true, true, true, true, true, true, true, true, 0)
	Alias_Altar.GetRef().PlayAnimation("Down")
	Alias_RustyMaceIntRef.GetRef().Disable(false)
	DA10HauntingController.SetStage(90)
	Alias_MainDoor.GetRef().Lock(false, false)
	DA10NonStaticBedEnabler.Enable(false)
	Alias_Logrolf.GetActorRef().Moveto(Alias_CaptiveMarker.GetRef(), 0.000000, 0.000000, 0.000000, true)
	Alias_Logrolf.GetActorRef().Enable(false)
	Alias_Logrolf.GetActorRef().PlaceatMe(BoundCaptiveMarker as form, 1, false, false)
	Alias_Logrolf.GetActorRef().SetRestrained(1 as Bool)
	Alias_MapMarker.GetRef().AddtoMap(false)
	utility.Wait(2 as Float)
	Alias_Altar.GetRef().BlockActivation(true)
	game.GetPlayer().PlayIdle(IdleCowerExit)
endFunction

function Fragment_17()

	AchievementsQuest.IncDaedricQuests()
	self.SetObjectiveCompleted(70, 1 as Bool)
	self.Stop()
endFunction
