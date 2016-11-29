import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.text.*;

public class front
{
    private JTextArea tarea;
    private JComboBox cbox;
    private JTextField lineField;
    private String[] colourNames = {"RED", "ORANGE", "CYAN"};

    private Highlighter.HighlightPainter painter;

    private void createAndDisplayGUI()
    {
        final JFrame frame = new JFrame("STACY - A Static Analysis Tool");
        frame.setBounds(15, 15, 50, 35);
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        JPanel contentPane = new JPanel();
        contentPane.setBorder(BorderFactory.createTitledBorder(
                BorderFactory.createEmptyBorder(15, 15, 15, 15), "Enter code here"));

        tarea = new JTextArea(30,55);
        JScrollPane scrollPane = new JScrollPane(tarea);
        contentPane.add(scrollPane);

        JButton button = new JButton("Analyze");
        button.setBounds(113, 505, 84, 29);
        button.addActionListener(new ActionListener()
        {
            public void actionPerformed(ActionEvent ae)
            {
                int selection = JOptionPane.showConfirmDialog(
                        frame, getOptionPanel(), "Highlighting Options : ", JOptionPane.OK_CANCEL_OPTION
                                                , JOptionPane.PLAIN_MESSAGE);
                if (selection == JOptionPane.OK_OPTION)                             
                {
                    System.out.println("OK Selected");
                    int lineNumber = Integer.parseInt(lineField.getText().trim());
                    try
                    {
                        int startIndex = tarea.getLineStartOffset(lineNumber);
                        int endIndex = tarea.getLineEndOffset(lineNumber);
                        String colour = (String) cbox.getSelectedItem();

                        if (colour == colourNames[0])
                        {
                            System.out.println("RED Colour");
                            painter = new DefaultHighlighter.DefaultHighlightPainter(Color.RED);
                            tarea.getHighlighter().addHighlight(startIndex, endIndex, painter);
                        }
                        else if (colour == colourNames[1])
                        {
                            System.out.println("ORANGE Colour");
                            painter = new DefaultHighlighter.DefaultHighlightPainter(Color.ORANGE);
                            tarea.getHighlighter().addHighlight(startIndex, endIndex, painter);
                        }
                        else if (colour == colourNames[2])
                        {
                            System.out.println("CYAN Colour");
                            painter = new DefaultHighlighter.DefaultHighlightPainter(Color.CYAN);
                            tarea.getHighlighter().addHighlight(startIndex, endIndex, painter);
                        }
                    }
                    catch(BadLocationException ble)
                    {
                        ble.printStackTrace();
                    }
                }
                else if (selection == JOptionPane.CANCEL_OPTION)
                {
                    System.out.println("CANCEL Selected");
                }
                else if (selection == JOptionPane.CLOSED_OPTION)
                {
                    System.out.println("JOptionPane closed deliberately.");
                }
            }
        });
        frame.getContentPane().add(button);
        
        JButton btnDone = new JButton("Done");
		btnDone.setBounds(436, 505, 77, 29);
		btnDone.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent ae)
			{
				System.exit(0);
			}
		});
		frame.getContentPane().add(btnDone);
		
        frame.add(contentPane, BorderLayout.CENTER);
    
        frame.pack();
        frame.setLocationByPlatform(true);
        frame.setVisible(true);
    }

    private JPanel getOptionPanel()
    {
        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(0, 2, 5, 5));

        JLabel lineNumberLabel = new JLabel("Enter Line Number : ");
        lineField = new JTextField(10);

        JLabel colourLabel = new JLabel("Select One Colour : ");
        cbox = new JComboBox(colourNames);

        panel.add(lineNumberLabel);
        panel.add(lineField);
        panel.add(colourLabel);
        panel.add(cbox);

        return panel;
    }
    

    public static void main(String[] args)
    {
        SwingUtilities.invokeLater(new Runnable()
        {
            public void run()
            {
                new AgainTrial().createAndDisplayGUI();
            }
        });
    }
}

