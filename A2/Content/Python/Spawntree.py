import unreal
import random
import sys
  
def spawnTree(pos, rot, scale):
    bpName = '/Game/A1/CollectableItem/BP_Tree.BP_Tree'
    bpClass = unreal.EditorAssetLibrary.load_blueprint_class(bpName)
   
  
    if bpClass:
        actor = unreal.EditorLevelLibrary.spawn_actor_from_class(bpClass, pos, rot)
        actor.set_actor_scale3d(scale)
  
if len(sys.argv) > 1:
    numTrees = int(float(sys.argv[1]))
    
# Verify numTrees is a reasonable number
# Call spawn tree with the following types:
#    unreal.Vector for pos and scale
#    unreal.Rotator for rot



with unreal.ScopedEditorTransaction('Spawned Trees')as transaction:
    
    for i in range(5):
        a = random.randint(-1000,1001)
        b = random.randint(-1000,1001)

        pos = unreal.Vector(a,b,0)
        rot = unreal.Rotator(0,0,random.randint(0,360))
        scale = unreal.Vector(1,1,1)

        spawnTree(pos, rot, scale) # call the func or it won't work...
