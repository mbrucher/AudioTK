<map version="freeplane 1.2.0">
<!--To view this file, download free mind mapping software Freeplane from http://freeplane.sourceforge.net -->
<node TEXT="ATK" ID="ID_1723255651" CREATED="1283093380553" MODIFIED="1391880678520"><hook NAME="MapStyle">
    <conditional_styles>
        <conditional_style ACTIVE="true" LOCALIZED_STYLE_REF="AutomaticLayout.level,1" LAST="false">
            <node_level_condition VALUE="1" MATCH_CASE="false" MATCH_APPROXIMATELY="false" COMPARATION_RESULT="0" SUCCEED="true"/>
        </conditional_style>
        <conditional_style ACTIVE="true" LOCALIZED_STYLE_REF="AutomaticLayout.level,2" LAST="false">
            <node_level_condition VALUE="2" MATCH_CASE="false" MATCH_APPROXIMATELY="false" COMPARATION_RESULT="0" SUCCEED="true"/>
        </conditional_style>
        <conditional_style ACTIVE="true" LOCALIZED_STYLE_REF="AutomaticLayout.level,3" LAST="false">
            <node_level_condition VALUE="3" MATCH_CASE="false" MATCH_APPROXIMATELY="false" COMPARATION_RESULT="0" SUCCEED="true"/>
        </conditional_style>
        <conditional_style ACTIVE="true" LOCALIZED_STYLE_REF="AutomaticLayout.level,4" LAST="false">
            <node_level_condition VALUE="4" MATCH_CASE="false" MATCH_APPROXIMATELY="false" COMPARATION_RESULT="0" SUCCEED="true"/>
        </conditional_style>
    </conditional_styles>

<map_styles>
<stylenode LOCALIZED_TEXT="styles.root_node">
<stylenode LOCALIZED_TEXT="styles.predefined" POSITION="right">
<stylenode LOCALIZED_TEXT="default" MAX_WIDTH="600" COLOR="#000000" STYLE="as_parent">
<font NAME="SansSerif" SIZE="10" BOLD="false" ITALIC="false"/>
</stylenode>
<stylenode LOCALIZED_TEXT="defaultstyle.details"/>
<stylenode LOCALIZED_TEXT="defaultstyle.note"/>
<stylenode LOCALIZED_TEXT="defaultstyle.floating">
<edge STYLE="hide_edge"/>
<cloud COLOR="#f0f0f0" SHAPE="ROUND_RECT"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.user-defined" POSITION="right">
<stylenode LOCALIZED_TEXT="styles.topic" COLOR="#18898b" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subtopic" COLOR="#cc3300" STYLE="fork">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.subsubtopic" COLOR="#669900">
<font NAME="Liberation Sans" SIZE="10" BOLD="true"/>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.important">
<icon BUILTIN="yes"/>
</stylenode>
</stylenode>
<stylenode LOCALIZED_TEXT="styles.AutomaticLayout" POSITION="right">
<stylenode LOCALIZED_TEXT="AutomaticLayout.level.root" COLOR="#000000">
<font SIZE="18"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,1" COLOR="#18898b">
<font SIZE="16"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,2" COLOR="#cc3300">
<font SIZE="14"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,3" COLOR="#669900">
<font SIZE="12"/>
</stylenode>
<stylenode LOCALIZED_TEXT="AutomaticLayout.level,4" COLOR="#3333ff">
<font SIZE="10"/>
</stylenode>
</stylenode>
</stylenode>
</map_styles>
</hook>
<hook NAME="AutomaticEdgeColor" COUNTER="3"/>
<hook NAME="accessories/plugins/AutomaticLayout.properties" VALUE="ALL"/>
<node TEXT="C++" POSITION="right" ID="ID_768989959" CREATED="1391880696698" MODIFIED="1391880725917">
<edge COLOR="#7c7c00"/>
<cloud COLOR="#f0f0f0" SHAPE="ARC"/>
<node TEXT="Inputs" ID="ID_433901627" CREATED="1391880780872" MODIFIED="1391880782853">
<node TEXT="Wave" ID="ID_684320580" CREATED="1391880823695" MODIFIED="1395776883905">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="libsndfile" ID="ID_1688625522" CREATED="1395776865029" MODIFIED="1395776877665">
<icon BUILTIN="button_ok"/>
</node>
</node>
<node TEXT="Outputs" ID="ID_930469082" CREATED="1391880783401" MODIFIED="1391880785285">
<node TEXT="Wav" ID="ID_608818497" CREATED="1391880815415" MODIFIED="1395776880907">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="libsndfile" ID="ID_988853474" CREATED="1395776870126" MODIFIED="1395776874778">
<icon BUILTIN="button_ok"/>
</node>
</node>
<node TEXT="Core" ID="ID_1974077192" CREATED="1391880785936" MODIFIED="1391880790052">
<node TEXT="I/O conversion" ID="ID_1407202419" CREATED="1395777119051" MODIFIED="1395777131517">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Lag handling" ID="ID_912495434" CREATED="1395777049225" MODIFIED="1395777076701"/>
</node>
<node TEXT="Mock" ID="ID_3708272" CREATED="1391880790768" MODIFIED="1391880792093">
<node TEXT="White noise generator" ID="ID_355593601" CREATED="1391880840404" MODIFIED="1391880845936"/>
<node TEXT="Sinus generator" ID="ID_1654533231" CREATED="1395776832981" MODIFIED="1395776863220">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="FFT check" ID="ID_75194125" CREATED="1395776839589" MODIFIED="1395776860626">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Triangle generator" ID="ID_1452782039" CREATED="1395776842229" MODIFIED="1395776858530">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Triangle checker" ID="ID_1091000415" CREATED="1395776849798" MODIFIED="1395776855885">
<icon BUILTIN="button_ok"/>
</node>
</node>
<node TEXT="Tools" ID="ID_1857774892" CREATED="1395776810092" MODIFIED="1395776811544">
<node TEXT="Pan" ID="ID_295886939" CREATED="1395776812637" MODIFIED="1395776913542">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Sum" ID="ID_864094639" CREATED="1395776818457" MODIFIED="1395776911144">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Volume" ID="ID_358732341" CREATED="1395776820210" MODIFIED="1395776908354">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Downsampling" ID="ID_581251876" CREATED="1395776893748" MODIFIED="1395776905729">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Oversampling" ID="ID_639984442" CREATED="1395776898842" MODIFIED="1395776903124">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Optimizer" ID="ID_841054843" CREATED="1395776915459" MODIFIED="1395776919302">
<node TEXT="Scalar Newton" ID="ID_1878042242" CREATED="1395776920330" MODIFIED="1395776933791">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Vector Newton" ID="ID_1524410543" CREATED="1395776924516" MODIFIED="1395776931711"/>
</node>
</node>
<node TEXT="EQ" ID="ID_1077608646" CREATED="1391880792576" MODIFIED="1391880793476">
<node TEXT="FIR" ID="ID_1922442511" CREATED="1395776801932" MODIFIED="1395776806825">
<node TEXT="Parks-McClellan" ID="ID_361886951" CREATED="1396697977589" MODIFIED="1396698005264"/>
<node TEXT="Custom FIR" ID="ID_887007139" CREATED="1403022080196" MODIFIED="1403022084146">
<icon BUILTIN="button_ok"/>
</node>
</node>
<node TEXT="IIR" ID="ID_1108220244" CREATED="1403022047873" MODIFIED="1403022049640">
<node TEXT="Second Order" ID="ID_1755313817" CREATED="1391880827470" MODIFIED="1395776889873">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Bessel" ID="ID_1906874507" CREATED="1395776794549" MODIFIED="1397072812746">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Butterworth" ID="ID_324795407" CREATED="1395776798284" MODIFIED="1396820378337">
<icon BUILTIN="button_ok"/>
<node TEXT="Low pass" ID="ID_872643503" CREATED="1396697942476" MODIFIED="1396697962789">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="High pass" ID="ID_496704843" CREATED="1396697946054" MODIFIED="1396820368135">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Band pass" ID="ID_436674837" CREATED="1396697949182" MODIFIED="1396820371104">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Band stop" ID="ID_1553325121" CREATED="1396697952590" MODIFIED="1396820374148">
<icon BUILTIN="button_ok"/>
</node>
</node>
<node TEXT="Chebychev" ID="ID_665405476" CREATED="1396697967597" MODIFIED="1397311063407">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Elliptic" ID="ID_502660530" CREATED="1396697972341" MODIFIED="1403021915395">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="ToneStack" ID="ID_1639438755" CREATED="1403021907795" MODIFIED="1403021913259">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Custom IIR" ID="ID_1739603329" CREATED="1403022041705" MODIFIED="1403022086722">
<icon BUILTIN="button_ok"/>
</node>
</node>
</node>
<node TEXT="Distortion" ID="ID_900647788" CREATED="1395776976316" MODIFIED="1395776979784">
<node TEXT="Simple overdrive" ID="ID_700366864" CREATED="1395776980285" MODIFIED="1395777004168">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="SD1" ID="ID_1981074900" CREATED="1403021897302" MODIFIED="1403021902668">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Tube" ID="ID_1136898156" CREATED="1395776991563" MODIFIED="1395776998552"/>
</node>
<node TEXT="Dynamics" ID="ID_1198712523" CREATED="1391880793912" MODIFIED="1391880800651">
<node TEXT="Compressor" ID="ID_1390907338" CREATED="1396698023164" MODIFIED="1396698026167"/>
<node TEXT="Expander" ID="ID_1753212892" CREATED="1396698026948" MODIFIED="1396698029151"/>
<node TEXT="Limiter" ID="ID_1284280022" CREATED="1396698029651" MODIFIED="1396698032327"/>
</node>
<node TEXT="Amplifier" ID="ID_1018759378" CREATED="1396698010284" MODIFIED="1396698011952">
<node TEXT="Class A JLH" ID="ID_1358214729" CREATED="1396698012660" MODIFIED="1396698017447"/>
<node TEXT="Class B" ID="ID_1744793538" CREATED="1396698035435" MODIFIED="1396698037750"/>
</node>
<node TEXT="Delay" ID="ID_1014788473" CREATED="1403021920925" MODIFIED="1403021923371"/>
<node TEXT="Reverb" ID="ID_1321408765" CREATED="1403021924397" MODIFIED="1403021925587"/>
<node TEXT="Adaptive" ID="ID_1709833899" CREATED="1403021926492" MODIFIED="1403021929611"/>
</node>
<node TEXT="Python" POSITION="right" ID="ID_1591627391" CREATED="1391880715389" MODIFIED="1391880722615">
<edge COLOR="#ff0000"/>
<cloud COLOR="#f0f0f0" SHAPE="ARC"/>
<node TEXT="I/O in Numpy" ID="ID_1068189790" CREATED="1391880729781" MODIFIED="1396698059987">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Interface in Python" ID="ID_1495402697" CREATED="1391880745743" MODIFIED="1391880752452">
<node TEXT="Core" ID="ID_732685759" CREATED="1396698063733" MODIFIED="1396698144452">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Mock" ID="ID_803715432" CREATED="1396698068293" MODIFIED="1396698069857"/>
<node TEXT="Tools" ID="ID_311733524" CREATED="1396698070709" MODIFIED="1396698072024"/>
<node TEXT="EQ" ID="ID_1986435519" CREATED="1396698087460" MODIFIED="1396698150416">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Distortion" ID="ID_69692079" CREATED="1396698089884" MODIFIED="1396698168434">
<icon BUILTIN="button_ok"/>
</node>
<node TEXT="Dynamics" ID="ID_207123511" CREATED="1396698099452" MODIFIED="1396698103031"/>
<node TEXT="Amplifier" ID="ID_1785488241" CREATED="1396698103739" MODIFIED="1396698106247"/>
</node>
</node>
<node TEXT="Documentation" POSITION="right" ID="ID_876908940" CREATED="1403021966798" MODIFIED="1403021977407">
<edge COLOR="#0000ff"/>
<cloud COLOR="#f0f0f0" SHAPE="ARC"/>
<node TEXT="Doxygen" ID="ID_146103065" CREATED="1403022000120" MODIFIED="1403022004782"/>
<node TEXT="Tutorial" ID="ID_1707912100" CREATED="1403022005296" MODIFIED="1403022007742"/>
</node>
<node TEXT="Audio Plugins" POSITION="left" ID="ID_1643521236" CREATED="1403022014392" MODIFIED="1403022022848">
<edge COLOR="#00ff00"/>
<cloud COLOR="#f0f0f0" SHAPE="ARC"/>
<node TEXT="SD1 emulation" ID="ID_397879695" CREATED="1403022024465" MODIFIED="1403022030024"/>
</node>
</node>
</map>
