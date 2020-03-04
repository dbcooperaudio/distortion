#include "PluginEditor.hpp"


PluginEditor::PluginEditor(Plugin& p) : juce::AudioProcessorEditor(&p)
{
    setSize(400, 300);
}


void
PluginEditor::paint(
    juce::Graphics& g)
{
    g.fillAll(findColour(juce::ResizableWindow::backgroundColourId));
}


void
PluginEditor::resized()
{

}
