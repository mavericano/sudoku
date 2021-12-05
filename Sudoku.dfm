object Form1: TForm1
  Left = 0
  Top = 41
  Caption = 'Form1'
  ClientHeight = 472
  ClientWidth = 684
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesigned
  Scaled = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 477
    Top = 87
    Width = 125
    Height = 29
    Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object StringGrid1: TStringGrid
    Left = 8
    Top = 8
    Width = 455
    Height = 455
    Color = clWhite
    ColCount = 9
    DefaultColWidth = 50
    DefaultRowHeight = 50
    FixedCols = 0
    RowCount = 9
    FixedRows = 0
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Gadugi'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected, goEditing, goFixedRowDefAlign]
    ParentFont = False
    TabOrder = 0
    OnDrawCell = StringGrid1DrawCell
    OnSelectCell = StringGrid1SelectCell
    OnSetEditText = StringGrid1SetEditText
  end
  object Button1: TButton
    Left = 477
    Top = 8
    Width = 206
    Height = 73
    Caption = #1055#1088#1086#1074#1077#1088#1080#1090#1100' '#1088#1077#1096#1077#1085#1080#1077
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = Button1Click
  end
  object CheckBox1: TCheckBox
    Left = 485
    Top = 136
    Width = 128
    Height = 25
    Caption = #1055#1086#1076#1089#1074#1077#1090#1082#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = CheckBox1Click
  end
  object CheckBox2: TCheckBox
    Left = 485
    Top = 184
    Width = 164
    Height = 97
    Caption = #1044#1080#1085#1072#1084#1080#1095#1077#1089#1082#1072#1103' '#1087#1088#1086#1074#1077#1088#1082#1072' '#1086#1096#1080#1073#1086#1082
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    WordWrap = True
    OnClick = CheckBox2Click
  end
  object CheckBox3: TCheckBox
    Left = 485
    Top = 312
    Width = 164
    Height = 73
    Caption = #1044#1080#1085#1072#1084#1080#1095#1077#1089#1082#1072#1103' '#1089#1074#1077#1088#1082#1072' '#1089' '#1088#1077#1096#1077#1085#1080#1077#1084
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    WordWrap = True
    OnClick = CheckBox3Click
  end
  object MainMenu1: TMainMenu
    Left = 472
    Top = 432
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N2: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
        OnClick = N3Click
      end
    end
    object N4: TMenuItem
      Caption = #1055#1088#1072#1074#1080#1083#1072' '
      OnClick = N4Click
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 480
    Top = 392
  end
  object OpenDialog1: TOpenDialog
    Left = 512
    Top = 432
  end
end
